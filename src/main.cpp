#if not defined(ESP32)
#error This program is ESP32 only
#endif

// #define DEBUGLOG_DISABLE_LOG  // Comment it out to disable all logs
#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO

#define WIFI_SSID "AwesomeRobot"
#define WIFI_PASSWORD ""  // No password for open network

#define ULTRASONIC_SENSOR_TRIGGER_PIN 14
#define ULTRASONIC_SENSOR_ECHO_PIN 27
#define ULTRASONIC_SENSOR_MAX_DISTANCE 200

#define LEFT_GROUND_SENSOR_PIN 4
#define RIGHT_GROUND_SENSOR_PIN 15

#define MOTOR_LEFT_PIN1 32
#define MOTOR_LEFT_PIN2 33
#define MOTOR_LEFT_INVERT true
#define MOTOR_RIGHT_PIN1 25
#define MOTOR_RIGHT_PIN2 26
#define MOTOR_RIGHT_INVERT false

#define MOTOR_DRIVER_MAX_PWM 127
#define MOTOR_DRIVER_MIN_PWM -127
#define MOTOR_DRIVER_NEUTRAL_WIDTH 60

#include <Arduino.h>
#include <ArduinoJson.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <DRV8833MotorDriver.h>
#include <ESPAsyncWebServer.h>
#include <LedBlinker.h>
#include <NewPing.h>
#include "index_html_gz.h"
#include <RampFilter.h>
#include <SimpleDebugLog.h>
#include <SimpleWebSocketLog.h>
#include <WiFi.h>
#include <arduino-timer.h>

DRV8833 DRVLeft(MOTOR_LEFT_PIN1, MOTOR_LEFT_PIN2, MOTOR_LEFT_INVERT);
DRV8833 DRVRight(MOTOR_RIGHT_PIN1, MOTOR_RIGHT_PIN2, MOTOR_RIGHT_INVERT);

DRV8833MotorDriver motorLeft(DRVLeft);
DRV8833MotorDriver motorRight(DRVRight);

NewPing sonar(ULTRASONIC_SENSOR_TRIGGER_PIN, ULTRASONIC_SENSOR_ECHO_PIN, ULTRASONIC_SENSOR_MAX_DISTANCE);

LedBlinker builtInLed = LedBlinker(LED_BUILTIN, true);

IPAddress myIP;
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
DNSServer dnsServer;

auto timer = timer_create_default();

// Function declarations
int setupWifi();
int setupDnsServer();
int setupWebServer();
void handlePingHttpRequest(AsyncWebServerRequest* request);
int setupWebSocketServer();
void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);
void handleWebSocketMessage(void* arg, uint8_t* data, size_t len);
bool measureWithAllSensors(void*);
int sendDataToWebSocket(const char* type, const char* data);
int sendDataToWebSocket(const char* type, int data);
int sendDataToWebSocket(const char* type, bool data);

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

    builtInLed.begin();
    builtInLed.blinkContinuously(2000, 200);

    if (setupWifi()) LOG_ERROR("WiFi setup failed.");
    if (setupWebServer()) LOG_ERROR("Web server setup failed.");
    if (setupWebSocketServer()) LOG_ERROR("WebSocket server setup failed.");
    if (setupDnsServer()) LOG_ERROR("DNS server setup failed.");
    server.begin();

    // setup sensors
    pinMode(LEFT_GROUND_SENSOR_PIN, INPUT);
    pinMode(RIGHT_GROUND_SENSOR_PIN, INPUT);
    timer.every(500, measureWithAllSensors);

    LOG_INFO("Setup completed, time: ", millis());
}

void loop() {
    motorLeft.run();
    motorRight.run();
    builtInLed.run();
    timer.tick();
    dnsServer.processNextRequest();
}

// Function definitions
int setupWifi() {
    LOG_DEBUG("Setting up WiFi Access Point");

    if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
        LOG_ERROR("Soft AP creation failed.");
        LOG_ERROR("Boot stopped. Please restart the device manually.");
        while (true);
    }

    myIP = WiFi.softAPIP();
    LOG_INFO("Access Point IP address: ", myIP);

    return 0;
}

void handlePingHttpRequest(AsyncWebServerRequest* request) {
    LOG_INFO("Handling /ping HTTP request");
    request->send(200, "text/plain", "pong");
}

int setupWebServer() {
    LOG_DEBUG("Setting up web server");

    // Serve compressed HTML from program memory
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        AsyncWebServerResponse* response = request->beginResponse(200, "text/html", (const uint8_t*)index_html_gz, sizeof(index_html_gz));
        response->addHeader("Content-Encoding", "gzip");
        request->send(response);
    });
    server.on("/ping", HTTP_GET, handlePingHttpRequest);

    // Serves index.html for any path that isn't already handled
    server.onNotFound([](AsyncWebServerRequest* request) {
        LOG_INFO("Redirecting to / from ", request->url());
        request->redirect("/");
    });

    return 0;
}

int setupDnsServer() {
    LOG_DEBUG("Setting up DNS server");

    // Check if myIP is setted correctly
    if (myIP == IPAddress()) {
        LOG_ERROR("Invalid IP address for captive portal. Does the WiFi setup succeed?");
        return 1;
    }

    // Start DNS server on port 53 to intercept all DNS requests
    // Use a catch-all domain to redirect all DNS queries to the ESP32
    if (!dnsServer.start(53, "*", myIP)) {
        LOG_ERROR("DNS server failed to start");
        return 1;
    }
    LOG_INFO("DNS server started on port 53");
    return 0;
}

void handleWebSocketMessage(void* arg, uint8_t* data, size_t len) {
    LOG_DEBUG("WebSocket message received");
    JsonDocument doc;                                              // Allocate the JSON document
    DeserializationError error = deserializeJson(doc, data, len);  // Deserialize the JSON document

    // Test if parsing succeeds
    if (error) {
        LOG_ERROR("Failed to parse web socket JSON data: ", error.f_str());
        return;
    }

    // Handle the received data based on type
    if (doc["type"] == "joystick") {
        LOG_TRACE("Joystick data received");
        LOG_TRACE("  x: ", doc["x"].as<float>());
        LOG_TRACE("  y: ", doc["y"].as<float>());

    } else if (doc["type"] == "slider") {
        LOG_TRACE("Slider data received");
        LOG_TRACE("  Slider ID: ", doc["id"].as<String>());
        LOG_TRACE("  Slider Value: ", doc["value"].as<int>());

        if (doc["id"] == "slider1") {
            motorLeft.filter.setFilterFactor(doc["value"].as<int>());
            motorRight.filter.setFilterFactor(doc["value"].as<int>());

            LOG_WEBSOCKET("Acceleration set to: %d", doc["value"].as<int>());
        }

    } else if (doc["type"] == "switch") {
        LOG_TRACE("Switch data received");
        LOG_TRACE("  Switch ID: ", doc["id"].as<int>());
        LOG_TRACE("  Value: ", doc["value"].as<int>());

    } else if (doc["type"] == "push") {
        LOG_TRACE("Push button data received");
        LOG_TRACE("  Push button ID: ", doc["id"].as<int>());
        LOG_TRACE("  Value: ", doc["value"].as<int>());

    } else if (doc["type"] == "motor") {
        LOG_TRACE("Motor data received");
        LOG_TRACE("  Motor ID: ", doc["id"].as<String>());  // TODO: improve performance by using char[] instead of String
        LOG_TRACE("  Value: ", doc["value"].as<int>());

        if (doc["id"] == "leftDrive") {
            motorLeft.setSpeed(doc["value"].as<int>());
        } else if (doc["id"] == "rightDrive") {
            motorRight.setSpeed(doc["value"].as<int>());
        }

    } else {
        LOG_ERROR("Unknown data received from web socket");
    }
}

void onWebSocketEvent(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len) {
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
            LOG_TRACE("Ping received");
            break;
        case WS_EVT_PONG:
            LOG_TRACE("Pong received");
            break;
        case WS_EVT_ERROR:
            LOG_ERROR("WebSocket error");
            break;
    }
}

int setupWebSocketServer() {
    LOG_DEBUG("Setting up WebSocket server");
    ws.onEvent(onWebSocketEvent);

    // Clean up disconnected clients every 2 seconds
    timer.every(2000, [](void*) {
        ws.cleanupClients();
        LOG_TRACE("Cleaned up disconnected WebSocket clients");
        return true;  // return true to repeat the action
    });

    server.addHandler(&ws);
    LOG_INFO("WebSocket server setup completed");
    return 0;
}

bool measureWithAllSensors(void*) {
    LOG_DEBUG("Measuring with all sensors");
    static int leftGroundPrev = false;
    static int rightGroundPrev = false;
    static int distancePrev = -1;

    int leftGround = digitalRead(LEFT_GROUND_SENSOR_PIN);
    int rightGround = digitalRead(RIGHT_GROUND_SENSOR_PIN);
    int distance = sonar.ping_cm();  // get distance in centimeters

    LOG_TRACE("Left ground sensor value: ", leftGround);
    LOG_TRACE("Right ground sensor value: ", rightGround);
    LOG_TRACE("Ultrasonic sensor distance: ", distance);

    if (leftGround != leftGroundPrev) {
        LOG_WEBSOCKET("Left ground sensor value changed: %d", leftGround);
        sendDataToWebSocket("leftGround", leftGround);
        leftGroundPrev = leftGround;
    }

    if (rightGround != rightGroundPrev) {
        LOG_WEBSOCKET("Right ground sensor value changed: %d", rightGround);
        sendDataToWebSocket("rightGround", rightGround);
        rightGroundPrev = rightGround;
    }

    if (distance != distancePrev) {
        LOG_WEBSOCKET("Ultrasonic sensor distance changed: %d cm", distance);
        sendDataToWebSocket("sonar", distance);
        distancePrev = distance;
    }

    return true;  // return true to repeat the action - false to stop
}

int sendDataToWebSocket(const char* type, const char* value) {
    ws.printfAll("{\"type\":\"%s\",\"value\":\"%s\"}", type, value);
    return 0;
}

int sendDataToWebSocket(const char* type, int value) {
    ws.printfAll("{\"type\":\"%s\",\"value\":%d}", type, value);
    return 0;
}

int sendDataToWebSocket(const char* type, bool value) { return sendDataToWebSocket(type, value ? "true" : "false"); }
