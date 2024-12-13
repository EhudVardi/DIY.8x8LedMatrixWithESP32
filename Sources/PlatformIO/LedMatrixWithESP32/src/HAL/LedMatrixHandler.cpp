#include "LedMatrixHandler.h"

LedMatrixHandler::LedMatrixHandler(int size, int oe_pin, int data_pin, int latch_pin, int clock_pin)
    : N(size), _oe_pin(oe_pin), _data_pin(data_pin), _latch_pin(latch_pin), _clock_pin(clock_pin) {
    int numBytes = (N * N) / 8;
    matrix = new uint8_t[numBytes]();
    initPins();
}

LedMatrixHandler::~LedMatrixHandler() {
    delete[] matrix;
}

void LedMatrixHandler::clearMatrix() {
    memset(matrix, 0, N * N / 8);
}
uint8_t* LedMatrixHandler::getMatrix() {
    return matrix;
}
void LedMatrixHandler::setPixel(int x, int y, bool state) {
    int byteIndex = (x * N + y) / 8;
    int bitIndex = (x * N + y) % 8;
    if (state) {
        matrix[byteIndex] |= (1 << bitIndex);
    }
    else {
        matrix[byteIndex] &= ~(1 << bitIndex);
    }
}
bool LedMatrixHandler::getPixel(int x, int y) {
    int byteIndex = (x * N + y) / 8;
    int bitIndex = (x * N + y) % 8;
    return (matrix[byteIndex] & (1 << bitIndex)) != 0;
}
void LedMatrixHandler::render(){
    displayPattern(matrix);
}


void LedMatrixHandler::initPins() {
    pinMode(_oe_pin, OUTPUT);
    pinMode(_data_pin, OUTPUT);
    pinMode(_latch_pin, OUTPUT);
    pinMode(_clock_pin, OUTPUT);
    digitalWrite(_latch_pin, LOW); // Initialize Latch
    digitalWrite(_oe_pin, LOW); // Enable output
}
void LedMatrixHandler::displayPattern(byte pattern[32]) {
    for (int row = 0; row < 16; row++) {
        int16_t rowData = ~(1 << row);
        int16_t colData = ~((pattern[row * 2] << 8) | pattern[row * 2 + 1]);

        sendData(rowData, colData);
    }
}
void LedMatrixHandler::sendData(int16_t rowData, int16_t colData) {
    byte rowData_highByte = (rowData >> 8) & 0xFF;
    byte rowData_lowByte = rowData & 0xFF;
    byte colData_highByte = (colData >> 8) & 0xFF;
    byte colData_lowByte = colData & 0xFF;
    shiftOut(rowData_highByte);
    shiftOut(rowData_lowByte);
    shiftOut(colData_lowByte);
    shiftOut(colData_highByte);
    latch();
}
void LedMatrixHandler::shiftOut(byte data) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(_clock_pin, LOW);
        digitalWrite(_data_pin, data & (1 << (7 - i)) ? HIGH : LOW);
        delayMicroseconds(16);
        digitalWrite(_clock_pin, HIGH);
        delayMicroseconds(16);
    }
}
void LedMatrixHandler::latch() {
    // Latch the data
    digitalWrite(_latch_pin, HIGH);
    //delayMicroseconds(2); // Short delay to ensure data is latched
    digitalWrite(_latch_pin, LOW);
}