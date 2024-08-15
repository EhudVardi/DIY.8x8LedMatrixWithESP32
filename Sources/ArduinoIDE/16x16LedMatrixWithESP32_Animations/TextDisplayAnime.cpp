#include "TextDisplayAnime.h"
#include <unordered_map>

TextDisplayAnime::TextDisplayAnime(int size)
  : BaseInteractiveAnime(size), isScrolling(false) {
  stepDuration = 100;
  initializeCharacterMap();
}

void TextDisplayAnime::init() {
  setText("0123");
}

void TextDisplayAnime::initializeCharacterMap() {
  // Map characters to their 5x4 matrices (using 4x5 in byte form)
  characterMap['0'] = { 0b11111,
                        0b11001,
                        0b10011,
                        0b11111 };
  characterMap['1'] = { 0b00000,
                        0b00010,
                        0b11111,
                        0b00000 };
  characterMap['2'] = { 0b00000,
                        0b11001,
                        0b10101,
                        0b10011 };
  characterMap['3'] = { 0b00000,
                        0b10101,
                        0b10101,
                        0b11111 };
  // Add other character mappings (0-9, A-Z) here...
}

void TextDisplayAnime::setText(const std::string& text) {
  this->text = text;
  textIndex = 0;
  scrollOffset = 0;
}

void TextDisplayAnime::step() {
  // Clear the matrix
  clearMatrix();

  // Calculate xOffset to handle clipping in and out
  int xOffset = N - scrollOffset;

  // Iterate over the text in reverse order and map characters to the matrix
  for (auto it = text.rbegin(); it != text.rend(); ++it) {
    char c = *it;
    if (characterMap.find(c) != characterMap.end()) {
      // Only draw characters that are partially or fully visible
      if (xOffset < N && xOffset > -5) {
        addCharacterToMatrix(characterMap[c], xOffset);
      }
      xOffset += 5;  // Move to the next character's position
    }
  }

  if (isScrolling)
    scrollOffset++;

  // Reset the scrolling when the entire text has passed
  if (scrollOffset >= text.length() * 5 + N) {
    scrollOffset = 0;
  }
}

void TextDisplayAnime::addCharacterToMatrix(const std::array<byte, 4>& charMatrix, int xOffset) {
  for (int col = 0; col < 4; col++) {
    // Calculate the flipped column index
    int targetCol = xOffset + (3 - col);
    if (targetCol < 0 || targetCol >= N) continue;

    byte columnData = charMatrix[col];
    for (int row = 0; row < 5; row++) {
      bool isPixelOn = columnData & (1 << row);
      if (row < N && targetCol < N) {
        setPixel(row, targetCol, isPixelOn);
      }
    }
  }
}

void TextDisplayAnime::SetInputHandlers() {
  inputHandlers[0] = [this]() {
    stepDuration = max(10, stepDuration - 5);
  };
  inputHandlers[1] = [this]() {
    stepDuration = min(1000, stepDuration + 5);
  };
  inputHandlers[2] = [this]() {
    isScrolling = false;
  };
  inputHandlers[3] = [this]() {
    isScrolling = true;
  };
}
