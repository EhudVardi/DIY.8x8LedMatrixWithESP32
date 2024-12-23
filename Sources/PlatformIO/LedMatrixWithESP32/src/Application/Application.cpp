#include "Application.h"
#include "ApplicationConfig.h"

void Application::setup() {
    
    log("Initializing...");

    ledMatrixHandler = new LedMatrixHandler(DISPLAY_SCREEN_SIZE, DISPLAY_OE_PIN, DISPLAY_DATA_PIN, DISPLAY_LATCH_PIN, DISPLAY_CLOCK_PIN);

    // Initialize the AnimationManager
    animationManager = new AnimationManager(DISPLAY_SCREEN_SIZE);
    animationManager->init(ledMatrixHandler);

    // Setup button handlers
    std::vector<int> hwButtonPins = { BTN_DOWN_PIN, BTN_UP_PIN, BTN_LEFT_PIN, BTN_RIGHT_PIN, BTN_BACK_PIN, BTN_ENTER_PIN };
    std::vector<std::function<void()>> hwButtonHandlers_onPress = {
        [this]() { animationManager->getCurrentAnime()->SetInput(0); },
        [this]() { animationManager->getCurrentAnime()->SetInput(1); },
        [this]() { animationManager->getCurrentAnime()->SetInput(2); },
        [this]() { animationManager->getCurrentAnime()->SetInput(3); },
        [this]() { animationManager->initCurrAnime(ledMatrixHandler); },
        [this]() { animationManager->skipToNextAnime(ledMatrixHandler); }
    };
    std::vector<std::function<void()>> hwButtonHandlers_onRelease = {
        [this]() { animationManager->getCurrentAnime()->ResetInput(0); },
        [this]() { animationManager->getCurrentAnime()->ResetInput(1); },
        [this]() { animationManager->getCurrentAnime()->ResetInput(2); },
        [this]() { animationManager->getCurrentAnime()->ResetInput(3); },
        [this]() {},
        [this]() {}
    };
    hwButtonHandler = new HWButtonHandler(hwButtonPins, hwButtonHandlers_onPress, hwButtonHandlers_onRelease);

    log("Initialized.");
}

void Application::loop() {

    currentMillis = millis();
    
    BaseInteractiveAnime* currentAnime = animationManager->getCurrentAnime();
    if (currentMillis - previousMillis >= currentAnime->getStepDuration()) {
        previousMillis = currentMillis;
        currentAnime->step(ledMatrixHandler);
    }

    hwButtonHandler->updateButtons();
    
    ledMatrixHandler->render();
}
