#include "LedMatrixHandler.h"

LedMatrixHandler::LedMatrixHandler(int size)
    : N(size) {
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
    pinMode(OE_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    digitalWrite(LATCH_PIN, LOW); // Initialize Latch
    digitalWrite(OE_PIN, LOW); // Enable output
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
    shiftOut(rowData_highByte, CLOCK_PIN, DATA_PIN);
    shiftOut(rowData_lowByte, CLOCK_PIN, DATA_PIN);
    shiftOut(colData_lowByte, CLOCK_PIN, DATA_PIN);
    shiftOut(colData_highByte, CLOCK_PIN, DATA_PIN);
    latch(LATCH_PIN);
}
void LedMatrixHandler::shiftOut(byte data, int clockPin, int dataPin) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(clockPin, LOW);
        digitalWrite(dataPin, data & (1 << (7 - i)) ? HIGH : LOW);
        delayMicroseconds(16);
        digitalWrite(clockPin, HIGH);
        delayMicroseconds(16);
    }
}
void LedMatrixHandler::latch(int latchPin) {
    // Latch the data
    digitalWrite(latchPin, HIGH);
    //delayMicroseconds(2); // Short delay to ensure data is latched
    digitalWrite(latchPin, LOW);
}