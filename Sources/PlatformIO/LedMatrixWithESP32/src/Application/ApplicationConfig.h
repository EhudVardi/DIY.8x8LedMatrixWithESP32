#ifndef APPLICATION_CONFIG_H
#define APPLICATION_CONFIG_H

//DEFAULTS

//APPLICATION_CONFIG


//SYSTEM_HARDWARE
// DISPLAY
//  CONFIG
#define DISPLAY_SCREEN_SIZE 16  // bit size of the display (single dimension)
//  PINS
#define DISPLAY_OE_PIN 5        // Output Enable pin (active low)
#define DISPLAY_DATA_PIN 4      // Serial Data Input
#define DISPLAY_LATCH_PIN 2     // Latch Pin
#define DISPLAY_CLOCK_PIN 15    // Clock Pin

// INPUT
//  PINS
#define BTN_DOWN_PIN 13
#define BTN_UP_PIN 12
#define BTN_LEFT_PIN 14
#define BTN_RIGHT_PIN 27
#define BTN_BACK_PIN 33
#define BTN_ENTER_PIN 32

#endif // APPLICATION_CONFIG_H