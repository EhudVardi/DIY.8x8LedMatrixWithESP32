#ifndef THE_MATRIX_ANIME_H
#define THE_MATRIX_ANIME_H

#include "./../BaseInteractiveAnime.h"
#include <vector>

struct Line {
    int row;
    int col;
    int length;
};

class TheMatrixAnime : public BaseInteractiveAnime {
private:
    int maxLines;
    int minLineLength;
    int maxLineLength;
    int lineAppearanceRate;
    int currentStep;
    std::vector<Line> lines;

public:
    TheMatrixAnime(int size, int maxLines, int minLineLength, int maxLineLength, int lineAppearanceRate);
    void init(LedMatrixHandler* ledMatrixHandler) override;
    void step(LedMatrixHandler* ledMatrixHandler) override;
    void SetInputHandlers() override;

private:
    void clearLine(LedMatrixHandler* ledMatrixHandler, Line& line);
    void drawLine(LedMatrixHandler* ledMatrixHandler, Line& line);
};

#endif
