#include "BeatingHeartAnime.h"

BeatingHeartAnime::BeatingHeartAnime(int size)
  : BaseInteractiveAnime(size), stepCount(0) {
  stepDuration = 10;
  SetInputHandlers();
}

void BeatingHeartAnime::init() {
  stepCount = 0;
}

void BeatingHeartAnime::step() {
  if (stepCount < 5) {
    drawHeart(&smallHeart[0][0], 5);
  } else if (stepCount < 10) {
    drawHeart(&mediumHeart[0][0], 7);
  } else if (stepCount < 15) {
    drawHeart(&largeHeart[0][0], 9);
  } else if (stepCount < 20) {
    drawHeart(&mediumHeart[0][0], 7);
  } else if (stepCount < 25) {
    drawHeart(&largeHeart[0][0], 9);
  } else if (stepCount < 30) {
    drawHeart(&mediumHeart[0][0], 7);
  } else {
    drawHeart(&smallHeart[0][0], 5);
  }
  stepCount = (stepCount + 1) % 50;
}

void BeatingHeartAnime::drawHeart(const uint8_t* heart, int size) {
  int offset = (N - size) / 2;  // Centering offset
  clearMatrix();
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      // Compute the index in the 1D array
      int index = i * size + j;
      if (heart[index])
        setPixel(i + offset, j + offset, true);
      else
        setPixel(i + offset, j + offset, false);
    }
  }
}

void BeatingHeartAnime::SetInputHandlers() {
  inputHandlers[0] = [this]() {
    stepDuration = max(10, stepDuration - 5);
  };
  inputHandlers[1] = [this]() {
    stepDuration = min(1000, stepDuration + 5);
  };
  inputHandlers[2] = [this]() {
    stepDuration = max(10, stepDuration - 50);
  };
  inputHandlers[3] = [this]() {
    stepDuration = min(1000, stepDuration + 50);
  };
}
