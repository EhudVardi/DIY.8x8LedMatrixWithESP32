#include "BeatingHeartAnime.h"

BeatingHeartAnime::BeatingHeartAnime(int size) 
    : BaseInteractiveAnime(size), stepCount(0), direction(1) {
      stepDuration = 10;
    }

void BeatingHeartAnime::init() {
    stepCount = 0;
    direction = true;
}

void BeatingHeartAnime::step() {
    if (stepCount < 5) {
        drawHeart(&smallHeart[0][0], 5);
    } else if (stepCount < 10) {
        drawHeart(&mediumHeart[0][0], 7);
    } else {
        drawHeart(&largeHeart[0][0], 9);
    }

    stepCount = (direction ? stepCount+1 : stepCount-1);
    if (stepCount >= 15)
        direction = false;
    else if (stepCount <= 0)
        direction = true;

}

void BeatingHeartAnime::drawHeart(const uint8_t* heart, int size) {
    int offset = (N - size) / 2; // Centering offset
    clearMatrix();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            // Compute the index in the 1D array
            int index = i * size + j;
            if (heart[index])
              setPixel(i + offset, j + offset , true);
            else 
              setPixel(i + offset, j + offset , false);
        }
    }
}

