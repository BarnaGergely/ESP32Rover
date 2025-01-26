#ifndef ESP32
Critical error : This program is ESP32 only
#endif

#include <Arduino.h>
#include <AsyncTCP.h>
#include <DNSServer.h>
#include <DRV8833.h>
#include <ESPAsyncWebServer.h>
#include <LedBlinker.h>
#include <LittleFS.h>
#include <WiFi.h>

#define DEBUG  // Comment this line to disable debug logs and build the app in release mode

#ifdef DEBUG
#define DEBUGLOG_DEFAULT_LOG_LEVEL_INFO  // In debug mode, set the default log level to INFO in DebugLog library
#endif

#ifndef DEBUG
#define DEBUGLOG_DISABLE_LOG  // In release mode, disable all logs
#endif

#include <DebugLog.h>

#ifdef DEBUG
#define WOKWI  // In debug mode, turn on features for WokWi simulation
#endif

#define MOTOR_LEFT_PIN1 2
#define MOTOR_LEFT_PIN2 3
#define MOTOR_RIGHT_PIN1 4
#define MOTOR_RIGHT_PIN2 5

#define MOTOR_DRIVER_LEFT_INVERT false
#define MOTOR_DRIVER_RIGHT_INVERT false

#define MOTOR_DRIVER_MAX_PWM 127
#define MOTOR_DRIVER_MIN_PWM -128
#define MOTOR_DRIVER_RAMP_TIME 60
#define MOTOR_DRIVER_NEUTRAL_WIDTH 60
#define MOTOR_DRIVER_BRAKE false
#define MOTOR_DRIVER_NEUTRAL_BRAKE false
#include <MotorDriver.cpp>

#define WIFI_SSID "AwesomeRobot"
// You can remove the password parameter if you want the AP to be open.
// a valid password must have more than 7 characters
#define WIFI_PASSWORD "12345678"

                     // Global variables:
                     MotorDriver motorLeft(DRV8833(MOTOR_LEFT_PIN1, MOTOR_LEFT_PIN2, MOTOR_DRIVER_MIN_PWM, MOTOR_DRIVER_MAX_PWM, MOTOR_DRIVER_RAMP_TIME,
                                                   MOTOR_DRIVER_BRAKE, MOTOR_DRIVER_NEUTRAL_BRAKE));
MotorDriver motorRight(DRV8833(MOTOR_RIGHT_PIN1, MOTOR_RIGHT_PIN2, MOTOR_DRIVER_MIN_PWM, MOTOR_DRIVER_MAX_PWM, MOTOR_DRIVER_RAMP_TIME, MOTOR_DRIVER_BRAKE,
                               MOTOR_DRIVER_NEUTRAL_BRAKE));

LedBlinker builtInLed = LedBlinker(LED_BUILTIN);

const char* htmlContent PROGMEM = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Sample HTML</title>
</head>
<body>
    <h1>Hello, World!</h1>
    <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
</body>
</html>
)";

IPAddress myIP;
// DNSServer dnsServer;
AsyncWebServer webServer(80);

// Function declarations:
int setupWifi();
int mapRestEndpoints();
int setupWebServer();

// Main program:
void setup() {
    // make sure the motors are turned off
    motorLeft.stop();
    motorRight.stop();

    Serial.begin(115200);
    delay(500);  // Give some time to connect to the serial monitor

    builtInLed.begin();
    builtInLed.blinkContinuously(200, 2000);

    if (setupWifi()) {
        LOG_ERROR("WiFi setup failed.");
    }

    // LittleFS.begin(true);

    LOG_INFO("Setup completed");
}

void loop() {
    builtInLed.run();
    // dnsServer.processNextRequest();
#ifdef WOKWI
    delay(10);  // this speeds up the WokWi simulation
#endif
}

// Function definitions:
int setupWifi() {
    LOG_INFO("Setting up WiFi Access Point");

    // Remove the password parameter, if you want the
    // AP (Access Point) to be open
    if (!WiFi.softAP(WIFI_SSID, WIFI_PASSWORD)) {
        LOG_ERROR("Soft AP creation failed.");
        LOG_ERROR("Boot stopped. Please restart the device manually.");
        while (1);
    }

    myIP = WiFi.softAPIP();
    LOG_INFO("AP IP address: ", myIP);

    return 0;
}

int setupWebServer() {
    LOG_INFO("Setting up web server");

    /*
    // by default DNSServer is started serving any "*" domain name. It will
    // reply AccessPoint's IP to all DNS request (this is required for Captive
    // Portal detection)
    if (dnsServer.start(53, "*", myIP)) {
        LOG_INFO("Started DNS server in captive portal-mode");
    } else {
        LOG_ERROR("Can't start DNS server!");
    }
    */

    mapRestEndpoints();
    webServer.begin();
    return 0;
}

int mapRestEndpoints() {
    webServer.on("/", HTTP_GET, [](AsyncWebServerRequest* request) { request->send(200, "text/html", htmlContent); });

    webServer.onNotFound([&](AsyncWebServerRequest* request) { request->send(200, "text/html", htmlContent); });

    return 0;
}