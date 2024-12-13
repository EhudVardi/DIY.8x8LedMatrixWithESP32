#ifndef LED_MATRIX_HANDLER_H
#define LED_MATRIX_HANDLER_H

#include <Arduino.h>
#include <stdint.h>

class LedMatrixHandler {
protected:
    int N;
    uint8_t* matrix;

    int _oe_pin, _data_pin, _latch_pin, _clock_pin;

public:
    LedMatrixHandler(int size, int oe_pin, int data_pin, int latch_pin, int clock_pin);
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
    void shiftOut(byte data);
    void latch();
};

#endif //LED_MATRIX_HANDLER_H
