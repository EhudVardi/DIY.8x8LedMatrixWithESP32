#include <Arduino.h>
#include "HAL/HWButtonHandler.h"
#include "HAL/LedMatrixHandler.h"
#include "GUI/AnimationManager.h"

#define SCREEN_SIZE 16

// Button pins and handlers
#define BTN_DOWN_PIN 13
#define BTN_UP_PIN 12
#define BTN_LEFT_PIN 14
#define BTN_RIGHT_PIN 27
#define BTN_BACK_PIN 33
#define BTN_ENTER_PIN 32

HWButtonHandler* hwButtonHandler = nullptr;
LedMatrixHandler* ledMatrixHandler = nullptr;
AnimationManager* animationManager = nullptr;

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    ledMatrixHandler = new LedMatrixHandler(SCREEN_SIZE);

    // Initialize the AnimationManager
    animationManager = new AnimationManager(SCREEN_SIZE);
    animationManager->init(ledMatrixHandler);

    // Setup button handlers
    std::vector<int> hwButtonPins = { BTN_DOWN_PIN, BTN_UP_PIN, BTN_LEFT_PIN, BTN_RIGHT_PIN, BTN_BACK_PIN, BTN_ENTER_PIN };
    std::vector<std::function<void()>> hwButtonHandlers_onPress = {
        []() { animationManager->getCurrentAnime()->SetInput(0); },
        []() { animationManager->getCurrentAnime()->SetInput(1); },
        []() { animationManager->getCurrentAnime()->SetInput(2); },
        []() { animationManager->getCurrentAnime()->SetInput(3); },
        []() { animationManager->initCurrAnime(ledMatrixHandler); },
        []() { animationManager->skipToNextAnime(ledMatrixHandler); }
    };
    std::vector<std::function<void()>> hwButtonHandlers_onRelease = {
        []() { animationManager->getCurrentAnime()->ResetInput(0); },
        []() { animationManager->getCurrentAnime()->ResetInput(1); },
        []() { animationManager->getCurrentAnime()->ResetInput(2); },
        []() { animationManager->getCurrentAnime()->ResetInput(3); },
        []() {},
        []() {}
    };

    hwButtonHandler = new HWButtonHandler(hwButtonPins, hwButtonHandlers_onPress, hwButtonHandlers_onRelease);

    Serial.println("Initialized.");
}

unsigned long previousMillis = 0;

void loop() {
    unsigned long currentMillis = millis();
    BaseInteractiveAnime* currentAnime = animationManager->getCurrentAnime();
    if (currentMillis - previousMillis >= currentAnime->getStepDuration()) {
        previousMillis = currentMillis;
        currentAnime->step(ledMatrixHandler);
    }

    hwButtonHandler->updateButtons();
    
    ledMatrixHandler->render();
}
