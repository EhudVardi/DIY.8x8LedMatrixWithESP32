#include "TheMatrixAnime.h"

TheMatrixAnime::TheMatrixAnime(int size, int maxLines, int minLineLength, int maxLineLength, int lineAppearanceRate)
    : BaseInteractiveAnime(size), maxLines(maxLines), minLineLength(minLineLength), maxLineLength(maxLineLength), lineAppearanceRate(lineAppearanceRate) {
    stepDuration = 100;
    SetInputHandlers();
}

void TheMatrixAnime::init() {
    lines.clear();
    currentStep = 0;
}

void TheMatrixAnime::step() {
    currentStep++; // Increment step counter
    // Randomly add a new line based on the appearance rate
    if (currentStep % lineAppearanceRate == 0 && lines.size() < maxLines) {
        int col = random(0, N);
        int length = random(minLineLength, maxLineLength + 1);
        lines.push_back({ 0, col, length });
    }
    // Update each line
    for (auto& line : lines) {
        clearLine(line); // Clear previous state of the line
        line.row++; // Move the line down
        drawLine(line); // Set new state of the line
        // Remove lines that have fully exited the screen
        if (line.row - line.length >= N) {
            line = lines.back();
            lines.pop_back();
        }
    }
}

void TheMatrixAnime::clearLine(Line& line) {
    for (int i = 0; i < line.length; i++) {
        int row = line.row - i;
        if (row >= 0 && row < N) {
            setPixel(line.col, row, false);
        }
    }
}

void TheMatrixAnime::drawLine(Line& line) {
    for (int i = 0; i < line.length; i++) {
        int row = line.row - i;
        if (row >= 0 && row < N) {
            setPixel(line.col, row, true);
        }
    }
}

void TheMatrixAnime::SetInputHandlers() {
    RegisterInputHandler(0, [this](bool isSet) {
        if (isSet)
            stepDuration = max(10, stepDuration - 10);
    });
    RegisterInputHandler(1, [this](bool isSet) {
        if (isSet)
            stepDuration = min(500, stepDuration + 10);
    });
    RegisterInputHandler(2, [this](bool isSet) {
        if (isSet)
            lineAppearanceRate = max(1, lineAppearanceRate - 1);
    });
    RegisterInputHandler(3, [this](bool isSet) {
        if (isSet)
            lineAppearanceRate = min(50, lineAppearanceRate + 1);
    });
}
