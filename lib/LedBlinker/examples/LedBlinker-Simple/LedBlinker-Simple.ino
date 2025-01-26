#include <LedBlinker.h>

LedBlinker led(LED_BUILTIN);

void setup {
    led.begin(); // This needed to be called in the setup.
    led.blinkContinuously(200, 1000); // Blink the LED continuously with 200ms on and 1000ms off loops.
}

void loop {
    // This needed to be called in the main loop.
    led.run(); // Do not use big delay() in the loop!
}