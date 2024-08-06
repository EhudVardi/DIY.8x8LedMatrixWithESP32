
#include "BaseAnime.h"
#include "TheMatrixAnime.h"
#include "BeatingHeartAnime.h"

#define SCREEN_SIZE 16

BaseAnime* animation = nullptr;


#define OE_PIN   4 // Output Enable pin (active low)
#define DATA_1_PIN 13 // Serial Data Input
#define LATCH_1_PIN 2 // Latch Pin
#define CLOCK_1_PIN 15 // Clock Pin

#define DATA_PIN DATA_1_PIN
#define LATCH_PIN LATCH_1_PIN
#define CLOCK_PIN CLOCK_1_PIN



void setup() {
  Serial.begin(115200);
  Serial.println("Initializing pins...");

  // set pins mode
  pinMode(OE_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  digitalWrite(LATCH_PIN, LOW); // Initialize Latch
  digitalWrite(OE_PIN, LOW); // Enable output

  Serial.println("Pins initialized.");
  
  
  animation = new TheMatrixAnime(SCREEN_SIZE, 16);
  animation->init();
}


const unsigned long stepFrameTime = 100;
unsigned long previousMillis = 0;

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= stepFrameTime) {
    previousMillis = currentMillis;
    animation->step();
  }
  
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

void sendData(int16_t rowData, int16_t colData)
{
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
    digitalWrite(clockPin, HIGH);
  }
}
void latch(int latchPin) {
    // Latch the data
    digitalWrite(latchPin, HIGH);
    //delayMicroseconds(2); // Short delay to ensure data is latched
    digitalWrite(latchPin, LOW);
}
