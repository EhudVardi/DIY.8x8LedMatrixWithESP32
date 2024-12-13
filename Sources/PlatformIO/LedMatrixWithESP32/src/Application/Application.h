#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>
#include "HAL/HWButtonHandler.h"
#include "HAL/LedMatrixHandler.h"
#include "GUI/AnimationManager.h"
#include "Data/Log/Log.h"

class Application {
private:
    HWButtonHandler* hwButtonHandler = nullptr;
    LedMatrixHandler* ledMatrixHandler = nullptr;
    AnimationManager* animationManager = nullptr;

    unsigned long previousMillis = 0;
    unsigned long currentMillis = 0;

public:
    void setup();
    void loop();
};

#endif // APPLICATION_H
