#include "BeatingHeartAnime.h"

BeatingHeartAnime::BeatingHeartAnime(int size)
    : BaseInteractiveAnime(), currHeartIndex(0) {
    stepDuration = 70;
    SetInputHandlers();
}

void BeatingHeartAnime::init(LedMatrixHandler* ledMatrixHandler) {}

void BeatingHeartAnime::step(LedMatrixHandler* ledMatrixHandler) {
    currHeartIndex = (currHeartIndex + 1) % heartMatrices.size();
    drawHeart(ledMatrixHandler, &heartMatrices[currHeartIndex][0][0], 12);
}

void BeatingHeartAnime::drawHeart(LedMatrixHandler* ledMatrixHandler, const uint8_t* heart, int size) {

    int N = ledMatrixHandler->getSize();

    int offset = (N - size) / 2;  // Centering offset
    ledMatrixHandler->clearMatrix();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Compute the index in the 1D array
            int index = i * size + j;
            ledMatrixHandler->setPixel(j + offset, i + offset, (bool)(heart[index]));
        }
    }
}

void BeatingHeartAnime::SetInputHandlers() {
    RegisterInputHandler(0, [this](bool isSet) {
        if (isSet)
            stepDuration = max(10, stepDuration - 5);
    });
    RegisterInputHandler(1, [this](bool isSet) {
        if (isSet)
            stepDuration = min(1000, stepDuration + 5);
    });
    RegisterInputHandler(2, [this](bool isSet) {
        if (isSet)
            stepDuration = max(10, stepDuration - 50);
    });
    RegisterInputHandler(3, [this](bool isSet) {
        if (isSet)
            stepDuration = min(1000, stepDuration + 50);
    });
}
