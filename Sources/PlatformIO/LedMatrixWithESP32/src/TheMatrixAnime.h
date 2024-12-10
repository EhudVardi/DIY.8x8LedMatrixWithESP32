#ifndef THE_MATRIX_ANIME_H
#define THE_MATRIX_ANIME_H

#include "BaseInteractiveAnime.h"
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
    void init() override;
    void step() override;
    void SetInputHandlers() override;

private:
    void clearLine(Line& line);
    void drawLine(Line& line);
};

#endif
