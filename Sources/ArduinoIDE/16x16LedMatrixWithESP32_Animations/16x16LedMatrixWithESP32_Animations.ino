#include "HWButtonHandler.h"
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

#define OE_PIN 5      // Output Enable pin (active low)
#define DATA_PIN 4    // Serial Data Input
#define LATCH_PIN 2   // Latch Pin
#define CLOCK_PIN 15  // Clock Pin


HWButtonHandler* hwButtonHandler = nullptr;
#define BTN_DOWN_PIN 13
#define BTN_UP_PIN 12
#define BTN_LEFT_PIN 14
#define BTN_RIGHT_PIN 27
#define BTN_BACK_PIN 33
#define BTN_ENTER_PIN 32


void setup() {
  Serial.begin(115200);
  Serial.println("Initializing pins...");

  // set pins mode
  pinMode(OE_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  digitalWrite(LATCH_PIN, LOW);  // Initialize Latch
  digitalWrite(OE_PIN, LOW);     // Enable output

  Serial.println("Pins initialized.");

  initCurrAnime();

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
  animation->init();
}


unsigned long previousMillis = 0;

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= animation->getStepDuration()) {
    previousMillis = currentMillis;
    animation->step();
  }

  hwButtonHandler->updateButtons();

  uint8_t* matrix = animation->getMatrix();
  displayPattern(matrix);

  //delay(10);
}

void displayPattern(byte pattern[32]) {
  for (int row = 0; row < 16; row++) {
    int16_t rowData = ~(1 << row);
    int16_t colData = ~((pattern[row * 2] << 8) | pattern[row * 2 + 1]);

    sendData(rowData, colData);
  }
}

void sendData(int16_t rowData, int16_t colData) {
  byte rowData_highByte = (rowData >> 8) & 0xFF;
  byte rowData_lowByte = rowData & 0xFF;
  byte colData_highByte = (colData >> 8) & 0xFF;
  byte colData_lowByte = colData & 0xFF;
  shiftOut(rowData_highByte, CLOCK_PIN, DATA_PIN);
  shiftOut(rowData_lowByte, CLOCK_PIN, DATA_PIN);
  shiftOut(colData_lowByte, CLOCK_PIN, DATA_PIN);
  shiftOut(colData_highByte, CLOCK_PIN, DATA_PIN);
  latch(LATCH_PIN);
}

void shiftOut(byte data, int clockPin, int dataPin) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, data & (1 << (7 - i)) ? HIGH : LOW);
    delayMicroseconds(16);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(16);
  }
}
void latch(int latchPin) {
  // Latch the data
  digitalWrite(latchPin, HIGH);
  //delayMicroseconds(2); // Short delay to ensure data is latched
  digitalWrite(latchPin, LOW);
}
