#include "TextDisplayAnime.h"
#include <unordered_map>

TextDisplayAnime::TextDisplayAnime(int size)
  : BaseInteractiveAnime(size), isScrolling(true) {
  stepDuration = 100;
  initializeCharacterMap();
  SetInputHandlers();
}

void TextDisplayAnime::init() {
  setText("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  //setText("נועם המעפן");
}

void TextDisplayAnime::initializeCharacterMap() {
  // Map characters to their 5x4 matrices (using 4x5 in byte form)
  // Digit characters (0-9)
  characterMap['0'] = { 0b11111,
                        0b10001,
                        0b10001,
                        0b11111 };
  characterMap['1'] = { 0b00000,
                        0b00010,
                        0b11111,
                        0b00000 };
  characterMap['2'] = { 0b11101,
                        0b10101,
                        0b10101,
                        0b10111 };
  characterMap['3'] = { 0b10101,
                        0b10101,
                        0b10101,
                        0b11111 };
  characterMap['4'] = { 0b00111,
                        0b00100,
                        0b11111,
                        0b00100 };
  characterMap['5'] = { 0b10111,
                        0b10101,
                        0b10101,
                        0b11101 };
  characterMap['6'] = { 0b11111,
                        0b10101,
                        0b10101,
                        0b11101 };
  characterMap['7'] = { 0b00001,
                        0b00001,
                        0b00001,
                        0b11111 };
  characterMap['8'] = { 0b11111,
                        0b10101,
                        0b10101,
                        0b11111 };
  characterMap['9'] = { 0b10111,
                        0b10101,
                        0b10101,
                        0b11111 };
  // English characters mapping (A-Z)
  characterMap['A'] = { 0b11111,
                        0b00101,
                        0b00101,
                        0b11111 };
  characterMap['B'] = { 0b11111,
                        0b10101,
                        0b10101,
                        0b01010 };
  characterMap['C'] = { 0b01110,
                        0b10001,
                        0b10001,
                        0b10001 };
  characterMap['D'] = { 0b11111,
                        0b10001,
                        0b10001,
                        0b01110 };
  characterMap['E'] = { 0b11111,
                        0b10101,
                        0b10101,
                        0b10001 };
  characterMap['F'] = { 0b11111,
                        0b00101,
                        0b00101,
                        0b00001 };
  characterMap['G'] = { 0b11111,
                        0b10001,
                        0b10101,
                        0b11101 };
  characterMap['H'] = { 0b11111,
                        0b00100,
                        0b00100,
                        0b11111 };
  characterMap['I'] = { 0b10001,
                        0b11111,
                        0b10001,
                        0b00000 };
  characterMap['J'] = { 0b11000,
                        0b10000,
                        0b10001,
                        0b01111 };
  characterMap['K'] = { 0b11111,
                        0b00100,
                        0b01010,
                        0b10001 };
  characterMap['L'] = { 0b11111,
                        0b10000,
                        0b10000,
                        0b10000 };
  characterMap['M'] = { 0b11111,
                        0b00010,
                        0b00010,
                        0b11111 };
  characterMap['N'] = { 0b11111,
                        0b00010,
                        0b00100,
                        0b11111 };
  characterMap['O'] = { 0b01110,
                        0b10001,
                        0b10001,
                        0b01110 };
  characterMap['P'] = { 0b11111,
                        0b00101,
                        0b00101,
                        0b00010 };
  characterMap['Q'] = { 0b01110,
                        0b10001,
                        0b01001,
                        0b10110 };
  characterMap['R'] = { 0b11111,
                        0b00101,
                        0b00101,
                        0b11010 };
  characterMap['S'] = { 0b10010,
                        0b10101,
                        0b10101,
                        0b01001 };
  characterMap['T'] = { 0b00001,
                        0b11111,
                        0b00001,
                        0b00000 };
  characterMap['U'] = { 0b01111,
                        0b10000,
                        0b10000,
                        0b01111 };
  characterMap['V'] = { 0b00111,
                        0b01000,
                        0b10000,
                        0b01111 };
  characterMap['W'] = { 0b11111,
                        0b01000,
                        0b01000,
                        0b11111 };
  characterMap['X'] = { 0b11011,
                        0b00100,
                        0b00100,
                        0b11011 };
  characterMap['Y'] = { 0b00011,
                        0b00100,
                        0b11100,
                        0b00011 };
  characterMap['Z'] = { 0b11001,
                        0b10101,
                        0b10101,
                        0b10011 };
  // Hebrew characters mapping (א-ת)
  characterMap['א'] = { 0b11101,
                        0b00010,
                        0b01100,
                        0b10011 };
  characterMap['ב'] = { 0b10000,
                        0b11111,
                        0b10001,
                        0b10001 };
  characterMap['ג'] = { 0b11111,
                        0b00101,
                        0b11001,
                        0b00000 };
  characterMap['ד'] = { 0b00001,
                        0b11111,
                        0b00001,
                        0b00001 };
  characterMap['ה'] = { 0b11111,
                        0b00001,
                        0b00001,
                        0b11001 };
  characterMap['ו'] = { 0b11111,
                        0b00001,
                        0b00000,
                        0b00000 };
  characterMap['ז'] = { 0b00010,
                        0b11111,
                        0b00001,
                        0b00000 };
  characterMap['ח'] = { 0b11111,
                        0b00001,
                        0b11111,
                        0b00001 };
  characterMap['ט'] = { 0b01111,
                        0b10000,
                        0b11001,
                        0b01111 };
  characterMap['י'] = { 0b00111,
                        0b00001,
                        0b00000,
                        0b00000 };
  characterMap['כ'] = { 0b01110,
                        0b10001,
                        0b10001,
                        0b00000 };
  characterMap['ל'] = { 0b01100,
                        0b10010,
                        0b10011,
                        0b00000 };
  characterMap['מ'] = { 0b11110,
                        0b10001,
                        0b00010,
                        0b11101 };
  characterMap['נ'] = { 0b11110,
                        0b10001,
                        0b10000,
                        0b00000 };
  characterMap['ס'] = { 0b01111,
                        0b10001,
                        0b10001,
                        0b01110 };
  characterMap['ע'] = { 0b00111,
                        0b01100,
                        0b10010,
                        0b10001 };
  characterMap['פ'] = { 0b01110,
                        0b10001,
                        0b10101,
                        0b10111 };
  characterMap['צ'] = { 0b11011,
                        0b10100,
                        0b10010,
                        0b10001 };
  characterMap['ק'] = { 0b01110,
                        0b11001,
                        0b00001,
                        0b11101 };
  characterMap['ר'] = { 0b11110,
                        0b00001,
                        0b00001,
                        0b00000 };
  characterMap['ש'] = { 0b11111,
                        0b11000,
                        0b10111,
                        0b01111 };
  characterMap['ת'] = { 0b11110,
                        0b00001,
                        0b11111,
                        0b11001 };
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
        setPixel(targetCol, row, isPixelOn);
      }
    }
  }
}

void TextDisplayAnime::SetInputHandlers() {
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
      isScrolling = false;
  });
  RegisterInputHandler(3, [this](bool isSet) {
    if (isSet)
      isScrolling = true;
  });
}
