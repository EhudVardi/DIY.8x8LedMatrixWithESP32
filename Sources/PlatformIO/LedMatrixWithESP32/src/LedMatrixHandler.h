#ifndef LED_MATRIX_HANDLER_H
#define LED_MATRIX_HANDLER_H

#include <Arduino.h>
#include <stdint.h>

class LedMatrixHandler {
protected:
    int N;
    uint8_t* matrix;

public:
    LedMatrixHandler(int size);
    ~LedMatrixHandler();
    
    void clearMatrix();
    uint8_t* getMatrix();
    void setPixel(int x, int y, bool state);
    bool getPixel(int x, int y);
};

#endif //LED_MATRIX_HANDLER_H
