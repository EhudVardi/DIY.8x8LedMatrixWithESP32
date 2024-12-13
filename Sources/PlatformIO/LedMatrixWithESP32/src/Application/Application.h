#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>
#include "HAL/HWButtonHandler.h"
#include "HAL/LedMatrixHandler.h"
#include "GUI/AnimationManager.h"
#include "Data/Log/Log.h"

#define SCREEN_SIZE 16

// Button pins and handlers
#define BTN_DOWN_PIN 13
#define BTN_UP_PIN 12
#define BTN_LEFT_PIN 14
#define BTN_RIGHT_PIN 27
#define BTN_BACK_PIN 33
#define BTN_ENTER_PIN 32

class Application {
private:
    HWButtonHandler* hwButtonHandler = nullptr;
    LedMatrixHandler* ledMatrixHandler = nullptr;
    AnimationManager* animationManager = nullptr;

    unsigned long previousMillis = 0;
    unsigned long currentMillis = millis();

public:
    void setup();
    void loop();
};

#endif // APPLICATION_H
