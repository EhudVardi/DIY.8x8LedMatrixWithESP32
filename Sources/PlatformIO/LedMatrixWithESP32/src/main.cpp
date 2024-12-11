#include <Arduino.h>

#include "HWButtonHandler.h"
#include "LedMatrixHandler.h"
#include "TheMatrixAnime.h"
#include "BeatingHeartAnime.h"
#include "SpiralAnime.h"
#include "SnakeInteractiveAnime.h"
#include "TextDisplayAnime.h"
#include "TetrisInteractiveAnime.h"

#define SCREEN_SIZE 16
#define ANIME_COUNT 6

BaseInteractiveAnime* animation = nullptr;
int currAnimeIndex = 4;

LedMatrixHandler* ledMatrixHandler = nullptr;

HWButtonHandler* hwButtonHandler = nullptr;
#define BTN_DOWN_PIN 13
#define BTN_UP_PIN 12
#define BTN_LEFT_PIN 14
#define BTN_RIGHT_PIN 27
#define BTN_BACK_PIN 33
#define BTN_ENTER_PIN 32


void initCurrAnime();


void setup() {
    Serial.begin(115200);
    Serial.println("Initializing...");

    ledMatrixHandler = new LedMatrixHandler(SCREEN_SIZE);

    std::vector<int> hwButtonPins = { BTN_DOWN_PIN, BTN_UP_PIN, BTN_LEFT_PIN, BTN_RIGHT_PIN, BTN_BACK_PIN, BTN_ENTER_PIN };
    std::vector<std::function<void()>> hwButtonHandlers_onPress = {
      []() {
        animation->SetInput(0);
      },
      []() {
        animation->SetInput(1);
      },
      []() {
        animation->SetInput(2);
      },
      []() {
        animation->SetInput(3);
      },
      []() {
        initCurrAnime();
      },
      []() {
        currAnimeIndex = (currAnimeIndex + 1) % ANIME_COUNT;
        initCurrAnime();
      }
    };
    std::vector<std::function<void()>> hwButtonHandlers_onRelease = {
      []() {
        animation->ResetInput(0);
      },
      []() {
        animation->ResetInput(1);
      },
      []() {
        animation->ResetInput(2);
      },
      []() {
        animation->ResetInput(3);
      },
      []() {},
      []() {}
    };
    hwButtonHandler = new HWButtonHandler(hwButtonPins, hwButtonHandlers_onPress, hwButtonHandlers_onRelease);

    initCurrAnime();

    Serial.println("Initialized.");
}

void initCurrAnime() {
    switch (currAnimeIndex) {
        case 0: animation = new TheMatrixAnime(SCREEN_SIZE, 32, 3, 8, 1); break;
        case 1: animation = new BeatingHeartAnime(SCREEN_SIZE); break;
        case 2: animation = new SpiralAnime(SCREEN_SIZE); break;
        case 3: animation = new SnakeInteractiveAnime(SCREEN_SIZE); break;
        case 4: animation = new TetrisInteractiveAnime(SCREEN_SIZE); break;
        case 5:
        default: animation = new TextDisplayAnime(SCREEN_SIZE); break;
    }
    animation->init(ledMatrixHandler);
}


unsigned long previousMillis = 0;

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= animation->getStepDuration()) {
        previousMillis = currentMillis;
        animation->step(ledMatrixHandler);
    }

    hwButtonHandler->updateButtons();

    ledMatrixHandler->render();

    //delay(10);
}