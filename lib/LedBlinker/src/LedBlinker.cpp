#include "LedBlinker.h"

#include "Arduino.h"

// #define DEBUG // Uncomment this line out to enable debug messages

void LedBlinker::blinkContinuously(unsigned duration, unsigned interval) {
    _blinkContinuouslyDuration = duration;
    _blinkContinuouslyInterval = interval;
#ifdef DEBUG
    Serial.println("Blinking in every " + String(interval) + "ms for " + String(duration) + "ms");
#endif
}

void LedBlinker::blink(unsigned milliseconds) {
    if (isBlinkOneActive()) return;

    turnOn();
    _blinkOneDuration = milliseconds;
    _OneBlinkStart = millis();
}

void LedBlinker::blinkBlocking(unsigned milliseconds) {
    turnOn();
    delay(milliseconds);
    turnOff();
}

void LedBlinker::disable() {
    if (_isLighting) turnOff();
    _isLightingEnabled = false;
}

void LedBlinker::enable() { _isLightingEnabled = true; }

void LedBlinker::turnOn() {
    if (!_isLightingEnabled) return;

    digitalWrite(_pin, HIGH);
    _isLighting = true;
#ifdef DEBUG
    Serial.println("Light turned on");
#endif
}

void LedBlinker::turnOff() {
    if (!_isLightingEnabled) return;

    digitalWrite(_pin, LOW);
    _isLighting = false;
#ifdef DEBUG
    Serial.println("Light turned off");
#endif
}

void LedBlinker::run() {
    if (!_isLightingEnabled) {
        if (_isLighting) turnOff();
        return;
    }

    unsigned long currentMillis = millis();

    if (isBlinkOneActive()) {
#ifdef DEBUG
        Serial.println("BlinkOne is Active");
#endif
        if (currentMillis - _OneBlinkStart >= _blinkOneDuration) {
            turnOff();
            _blinkOneDuration = 0;
        }
    }

    if (blinkContinuouslyActive()) {
#ifdef DEBUG
        Serial.println("blinkContinuously is Active");
        Serial.println("Off: " + String(currentMillis) + " - " + String(_lastblinkContinuouslyTurnedOn) + " >= " + String(_blinkContinuouslyDuration));
        Serial.println("On: " + String(currentMillis) + " - " + String(_lastblinkContinuouslyTurnedOff) + " >= " + String(_blinkContinuouslyInterval));
#endif

        // if the LED is on and the on duration has passed, turn it off
        if (_isLighting && (currentMillis - _lastblinkContinuouslyTurnedOn >= _blinkContinuouslyDuration)) {
            _lastblinkContinuouslyTurnedOff = currentMillis;
            turnOff();

            // if the LED is off and the off interval has passed, turn it on
        } else if (!_isLighting && (currentMillis - _lastblinkContinuouslyTurnedOff >= _blinkContinuouslyInterval)) {
            _lastblinkContinuouslyTurnedOn = currentMillis;
            turnOn();
        }
    }
}

void LedBlinker::begin() {
    pinMode(_pin, OUTPUT);
    turnOff();
    _isReady = true;
}

LedBlinker::LedBlinker(int pin) : _pin(pin) {}

bool LedBlinker::isBlinkOneActive() { return _blinkOneDuration > 0; }
bool LedBlinker::blinkContinuouslyActive() { return _blinkContinuouslyDuration > 0; }