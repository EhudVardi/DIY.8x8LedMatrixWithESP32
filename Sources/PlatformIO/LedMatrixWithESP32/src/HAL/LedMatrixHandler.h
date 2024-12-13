#ifndef LED_MATRIX_HANDLER_H
#define LED_MATRIX_HANDLER_H

#include <Arduino.h>
#include <stdint.h>

#define OE_PIN 5      // Output Enable pin (active low)
#define DATA_PIN 4    // Serial Data Input
#define LATCH_PIN 2   // Latch Pin
#define CLOCK_PIN 15  // Clock Pin

class LedMatrixHandler {
protected:
    int N;
    uint8_t* matrix;

public:
    LedMatrixHandler(int size);
    ~LedMatrixHandler();

    int getSize() { return N; }

    void clearMatrix();
    uint8_t* getMatrix();
    void setPixel(int x, int y, bool state);
    bool getPixel(int x, int y);
    void render();

private:
    void initPins();
    void displayPattern(byte pattern[32]);
    void sendData(int16_t rowData, int16_t colData);
    void shiftOut(byte data, int clockPin, int dataPin);
    void latch(int latchPin);
};

#endif //LED_MATRIX_HANDLER_H
