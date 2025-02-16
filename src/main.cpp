#if not defined(ESP32) && not defined(ESP8266)
Critical error : This program is ESP32 or ESP8266 only
#endif

#include <Arduino.h>
#include <DNSServer.h>  // TODO: do we really need this?

#ifdef ESP32
#include <AsyncTCP.h>
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif

#if defined(WOKWI)
#include <index_html.h>  // Stores the web page as plain text. Generated by the build process.
// #include <index_html_gz.h>  // Stores the web page as gzip compressed binaries. Generated by the build process.
#endif

#define DEVELOPER_MODE  // Comment this line to disable debug logs and build the app in release mode

#ifdef DEVELOPER_MODE
#define DEBUGLOG_DEFAULT_LOG_LEVEL_DEBUG  // In debug mode, set the default log level to INFO in DebugLog library
#endif

#ifndef DEVELOPER_MODE
#define DEBUGLOG_DISABLE_LOG  // In release mode, disable all logs
#endif

#include <ArduinoJson.h>
#include <DRV8833MotorDriver.h>
#include <ESPAsyncWebServer.h>
#include <HCSR04.h>
#include <LedBlinker.h>
#include <LittleFS.h>
#include <SimpleDebugLog.h>
#include <SimpleWebSocketLog.h>
#include <arduino-timer.h>

#ifdef DEVELOPER_MODE
// #define WOKWI  // In developer mode, turn on features for WokWi simulation
#endif

#define ULTRASONIC_SENSOR_TRIGGER_PIN D3    // D3 on D1 Mini
#define ULTRASONIC_SENSOR_ECHO_PIN D1       // D1 on D1 Mini
#define ULTRASONIC_SENSOR_MAX_DISTANCE 200  // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400.

#define LEFT_GROUND_SENSOR_PIN D8   // D8 on D1 Mini
#define RIGHT_GROUND_SENSOR_PIN A0  // A0 on D1 Mini

#define MOTOR_LEFT_PIN1 D7  // D7 on D1 Mini
#define MOTOR_LEFT_PIN2 D6  // D6 on D1 Mini
#define MOTOR_LEFT_INVERT true
#define MOTOR_RIGHT_PIN1 D5  // D5 on D1 Mini
#define MOTOR_RIGHT_PIN2 D0  // D0 on D1 Mini
#define MOTOR_RIGHT_INVERT false

#define MOTOR_DRIVER_MAX_PWM 127
#define MOTOR_DRIVER_MIN_PWM -127
#define MOTOR_DRIVER_NEUTRAL_WIDTH 60
#include <DRV8833MotorDriver.h>
#include <RampFilter.h>

#define WIFI_SSID "AwesomeRobot"
// You can remove the password parameter if you want the AP to be open.
// a valid password must have more than 7 characters
#define WIFI_PASSWORD ""

                                              DRV8833 DRVLeft(MOTOR_LEFT_PIN1, MOTOR_LEFT_PIN2, MOTOR_LEFT_INVERT);
DRV8833 DRVRight(MOTOR_RIGHT_PIN1, MOTOR_RIGHT_PIN2, MOTOR_RIGHT_INVERT);

// Global variables:
DRV8833MotorDriver motorLeft(DRVLeft);
DRV8833MotorDriver motorRight(DRVRight);

LedBlinker builtInLed = LedBlinker(LED_BUILTIN);

IPAddress myIP;
// DNSServer dnsServer;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

auto timer = timer_create_default();  // create a timer with default settings

/*
class CaptiveRequestHandler : public AsyncWebHandler {
   public:
    bool canHandle(__unused AsyncWebServerRequest *request) const override { return true; }

    // TODO: Customize this
    void handleRequest(AsyncWebServerRequest *request) { request->redirect("/"); }
};
*/

// Function declarations:
int setupWifiAP();
int setupWokwiWifi();
int setupWifi();
int setupWebServer();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
int setupWebSocketServer();
void handlePingHttpRequest(AsyncWebServerRequest *request);
bool measureWithAllSensors(void *);

// Main program:
void setup() {
    // Initialize the motor drivers
    motorLeft.filter.setFilterFactor(25);
    motorRight.filter.setFilterFactor(25);
    motorLeft.begin();
    motorRight.begin();

    Serial.begin(115200);
    delay(500);  // Give some time to connect to the serial monitor
    LOG_INFO("Starting setup");

    Serial.begin(115200);
    builtInLed.begin();
    builtInLed.blinkContinuously(2000, 200);

    if (setupWifi()) LOG_ERROR("WiFi setup failed.");
    if (setupWebServer()) LOG_ERROR("Web server setup failed.");
    if (setupWebSocketServer()) LOG_ERROR("WebSocket server setup failed.");
    server.begin();

    // Mount the file system
#ifndef WOKWI
#ifdef ESP32
    if (!LittleFS.begin(true)) LOG_ERROR("LittleFS Mount Failed");
#else
    if (!LittleFS.begin()) LOG_ERROR("LittleFS Mount Failed");
#endif
#endif
    if (!LittleFS.exists("/index.html")) LOG_ERROR("index.html not found in LittleFS");
    if (!LittleFS.exists("/index.html.gz")) LOG_ERROR("index.html.gz not found in LittleFS");

    // setup sensors
    pinMode(LEFT_GROUND_SENSOR_PIN, INPUT);
    pinMode(RIGHT_GROUND_SENSOR_PIN, INPUT);
    HCSR04.begin(ULTRASONIC_SENSOR_TRIGGER_PIN, ULTRASONIC_SENSOR_ECHO_PIN);
    timer.every(500, measureWithAllSensors);

    LOG_INFO("Setup completed, time: ", millis());
}

void loop() {
    motorLeft.run();
    motorRight.run();
    builtInLed.run();
    ws.cleanupClients();  // TODO: only run it in every 2 sec based on WebSockets example:
                          // https://github.com/ESP32Async/ESPAsyncWebServer/blob/main/examples/WebSocket/WebSocket.ino
    timer.tick();
    // dnsServer.processNextRequest();
#ifdef WOKWI
    delay(10);  // this speeds up the WokWi simulation
#endif
}

// Function definitions:
int setupWifi() {
    // WOKWI not supports Access Points, so we need to connect its wifi if we are using it
#ifdef WOKWI
    return setupWokwiWifi();
#else
    return setupWifiAP();
#endif
}

int setupWifiAP() {
    LOG_INFO("Setting up WiFi Access Point");

    // Remove the password parameter, if you want the
    // AP (Access Point) to be open
    if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
        LOG_ERROR("Soft AP creation failed.");
        LOG_ERROR("Boot stopped. Please restart the device manually.");
        while (1);
    }

    myIP = WiFi.softAPIP();
    LOG_INFO("Access Point IP address: ", myIP);

    return 0;
}

int setupWokwiWifi() {
    LOG_INFO("Connecting to virtual Wokwi WiFi");
    WiFi.begin("Wokwi-GUEST", "", 6);  // The WiFi channel 6 skips the WiFi scanning phase and saves about 4 seconds when connecting to the WiFi.
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
    }
    LOG_INFO("WiFi Connected!");
    return 0;
}

void handlePingHttpRequest(AsyncWebServerRequest *request) {
    LOG_INFO("Handling /ping HTTP request");
    request->send(200, "text/plain", "pong");
}

#if defined(WOKWI)
void handleRootGetHttpRequestWokwi(AsyncWebServerRequest *request) {
    LOG_INFO("Handling root GET HTTP request");
    LOG_INFO("Sending index.html:");
    AsyncWebServerResponse *response = request->beginResponse(200, "text/html", index_html);
    // response->addHeader("Content-Encoding", "gzip");
    request->send(response);
}
#endif

int setupWebServer() {
    LOG_INFO("Setting up web server");

    /*
    // by default the DNSServer is start serving any ("*") domain name.
    // It will reply Access Point's IP to all DNS request (this is required for Captive Portal detection)
    if (dnsServer.start(53, "*", WiFi.softAPIP())) {
        LOG_INFO("Started DNS server in captive portal-mode");
    } else {
        LOG_ERROR("Can't start DNS server!");
    }

    server.addHandler(new CaptiveRequestHandler()).setFilter(ON_AP_FILTER);  // only when requested from AP
    */
#ifdef WOKWI
    // Wokwi simulator does not support file system so we need to serve the index.html as a variable in simulation,
    // but in variable the gzip compression is not supported or I don't know how to use it. Maybe this is the problem:
    // https://stackoverflow.com/questions/73118165/how-to-get-gzip-compression-as-string
    server.on("/", HTTP_GET, handleRootGetHttpRequestWokwi);
#else
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) { request->redirect("/index.html"); });
    server.serveStatic("/index.html", LittleFS, "/index.html");
    server.on("/ping", HTTP_GET, handlePingHttpRequest);
#endif
    // server.onNotFound([](AsyncWebServerRequest *request) { request->send(404, "text/plain", "404 - Not found"); }); // TODO: this is not works with
    // serveStatic;
    return 0;
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
    LOG_DEBUG("WebSocket message received");
    // Allocate the JSON document
    JsonDocument doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, data, len);

    // Test if parsing succeeds
    if (error) {
        LOG_ERROR("Failed to parse JSON data: ", error.f_str());
        return;
    }

    // Handle the received data based on type
    if (doc["type"] == "joystick") {
        LOG_INFO("Joystick data received");
        LOG_INFO("  x: ", doc["x"].as<float>());
        LOG_INFO("  y: ", doc["y"].as<float>());

    } else if (doc["type"] == "slider") {
        LOG_INFO("Slider data received");
        LOG_INFO("  Slider ID: ", doc["id"].as<String>());
        LOG_INFO("  Slider Value: ", doc["value"].as<int>());

        if (doc["id"] == "slider1") {
            motorLeft.filter.setFilterFactor(doc["value"].as<int>());
            motorRight.filter.setFilterFactor(doc["value"].as<int>());

            LOG_WEBSOCKET("Acceleration set to: %d", doc["value"].as<int>());
        }

    } else if (doc["type"] == "switch") {
        LOG_INFO("Switch data received");
        LOG_INFO("  Switch ID: ", doc["id"].as<int>());
        LOG_INFO("  Value: ", doc["value"].as<int>());

    } else if (doc["type"] == "push") {
        LOG_INFO("Push button data received");
        LOG_INFO("  Push button ID: ", doc["id"].as<int>());
        LOG_INFO("  Value: ", doc["value"].as<int>());

    } else if (doc["type"] == "motor") {
        LOG_INFO("Motor data received");
        LOG_INFO("  Motor ID: ", doc["id"].as<String>());  // TODO: improve performance by using char[] instead of String
        LOG_INFO("  Value: ", doc["value"].as<int>());

        if (doc["id"] == "leftDrive") {
            motorLeft.setSpeed(doc["value"].as<int>());
        } else if (doc["id"] == "rightDrive") {
            motorRight.setSpeed(doc["value"].as<int>());
        }

    } else {
        LOG_INFO("Unknown data received");
    }
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
    LOG_DEBUG("WebSocket event received");
    switch (type) {
        case WS_EVT_CONNECT:
            LOG_INFO("WebSocket client #", client->id());
            LOG_INFO("  connected from ", client->remoteIP().toString().c_str());
            break;
        case WS_EVT_DISCONNECT:
            LOG_INFO("WebSocket client disconnected: #", client->id());
            break;
        case WS_EVT_DATA:
            handleWebSocketMessage(arg, data, len);
            break;
        case WS_EVT_PING:
            LOG_INFO("Ping received");
            break;
        case WS_EVT_PONG:
            LOG_INFO("Pong received");
            break;
        case WS_EVT_ERROR:
            LOG_ERROR("WebSocket error");
            break;
    }
}

int setupWebSocketServer() {
    LOG_INFO("Setting up WebSocket server");
    ws.onEvent(onWebSocketEvent);
    server.addHandler(&ws);
    return 0;
}

bool measureWithAllSensors(void *) {
    LOG_DEBUG("Measuring with all sensors");
    static bool leftGroundPrev = false;
    static bool rightGroundPrev = false;
    static int distancePrev = -1;

    bool leftGround = digitalRead(LEFT_GROUND_SENSOR_PIN);
    bool rightGround = digitalRead(RIGHT_GROUND_SENSOR_PIN);
    double *distances = HCSR04.measureDistanceCm(); // returns an array, because the library supports multiple sensors

    int distance = (int)distances[0]; // the ultrasonic sensor is very inaccurate, so we don't need the decimal part

    LOG_DEBUG("Left ground sensor value: ", leftGround);
    LOG_DEBUG("Right ground sensor value: ", rightGround);
    LOG_DEBUG("Ultrasonic sensor distance: ", distance);

    // TODO: crashes somwhere here
    if (leftGround != leftGroundPrev) {
        LOG_WEBSOCKET("Left ground sensor value changed: %d", leftGround);
        leftGroundPrev = leftGround;
    }

    if (rightGround != rightGroundPrev) {
        LOG_WEBSOCKET("Right ground sensor value changed: %d", rightGround);
        rightGroundPrev = rightGround;
    }

    if (distance != distancePrev) {
        LOG_WEBSOCKET("Ultrasonic sensor distance changed: %d cm", distance);
        distancePrev = distance;
    }

    return true;  // to repeat the action - false to stop
}