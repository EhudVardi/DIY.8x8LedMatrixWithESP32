#include "TheMatrixAnime.h"

TheMatrixAnime::TheMatrixAnime(int size, int maxPixels)
  : BaseInteractiveAnime(size), maxPixels(maxPixels) {
  stepDuration = 100;
  SetInputHandlers();
}

void TheMatrixAnime::init() {
  pixels.clear();
}

void TheMatrixAnime::step() {
  if (pixels.size() < maxPixels) {
    int col = random(0, N);
    pixels.push_back({ 0, col });
  }

  for (auto& pixel : pixels) {
    setPixel(pixel.first, pixel.second, false);
    pixel.first++;
    if (pixel.first >= N) {
      pixel.first = 0;
      pixel.second = random(0, N);
    }
    setPixel(pixel.first, pixel.second, true);
  }
}

void TheMatrixAnime::SetInputHandlers() {
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
