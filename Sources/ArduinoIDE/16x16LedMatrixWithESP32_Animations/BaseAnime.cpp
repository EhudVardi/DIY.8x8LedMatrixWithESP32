#include "BaseAnime.h"

BaseAnime::BaseAnime(int size) : N(size) {
    int numBytes = (N * N) / 8;
    matrix = new uint8_t[numBytes]();
}

BaseAnime::~BaseAnime() {
    delete[] matrix;
}

void BaseAnime::clearMatrix() {
    memset(matrix, 0, N * N / 8);
}

uint8_t* BaseAnime::getMatrix() {
    return matrix;
}

void BaseAnime::setPixel(int x, int y, bool state) {
    int byteIndex = (x * N + y) / 8;
    int bitIndex = (x * N + y) % 8;
    if (state) {
        matrix[byteIndex] |= (1 << bitIndex);
    } else {
        matrix[byteIndex] &= ~(1 << bitIndex);
    }
}

bool BaseAnime::getPixel(int x, int y) {
    int byteIndex = (x * N + y) / 8;
    int bitIndex = (x * N + y) % 8;
    return (matrix[byteIndex] & (1 << bitIndex)) != 0;
}
