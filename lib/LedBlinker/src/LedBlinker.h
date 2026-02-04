#ifndef LED_BLINKER_H
#define LED_BLINKER_H

#include <Arduino.h>

/**
 * @brief Simple Arduino library to control LEDs in a non-blocking way. Especially designed for making status blinks with built-in LEDs.
 */
class LedBlinker {
   public:
    /**
     * @brief Starts the LED blinking continuously.
     *
     * @param duration The duration for which the LED stays on in each blink cycle (in milliseconds).
     * @param interval The interval between each blink (in milliseconds).
     */
    void blinkContinuously(unsigned duration, unsigned interval);

    /**
     * @brief Blinks the LED once for a specified duration.
     *
     * @param milliseconds The duration for which the LED stays on (in milliseconds). Default is 300ms.
     */
    void blink(unsigned milliseconds = 300);

    /**
     * @brief Blinks the LED once for a specified duration, blocking the execution.
     *
     * @param milliseconds The duration for which the LED stays on (in milliseconds). Default is 300ms.
     */
    void blinkBlocking(unsigned milliseconds = 300);

    /**
     * @brief Disables the LED - and makes it impossible to turn on.
     */
    void disable();

    /**
     * @brief Enables the LED - makes it possible to turn on.
     */
    void enable();

    /**
     * @brief Turns on the LED.
     */
    void turnOn();

    /**
     * @brief Turns off the LED.
     */
    void turnOff();

    /**
     * @brief Runs the LED control logic. Should be called repeatedly in the main loop.
     */
    void run();

    /**
     * @brief Sets up the LED.
     */
    void begin();

    /**
     * @brief Constructor to initialize the LedBlinker with a specific pin.
     *
     * @param pin The pin number to which the LED is connected.
     */
    LedBlinker(int pin, bool inverted = false);

   private:
    int _pin;
    bool _inverted = false;
    bool _isReady = false;

    unsigned _blinkOneDuration = 0;
    unsigned long _OneBlinkStart = 0;

    unsigned long _blinkContinuouslyDuration = 0;
    unsigned long _blinkContinuouslyInterval = 0;
    unsigned long _lastblinkContinuouslyTurnedOn = 0;
    unsigned long _lastblinkContinuouslyTurnedOff = 0;

    bool _isLighting = false;
    bool _isLightingEnabled = true;

    bool isBlinkOneActive();
    bool blinkContinuouslyActive();
};

#endif