#ifndef THE_MATRIX_ANIME_H
#define THE_MATRIX_ANIME_H

#include "BaseAnime.h"
#include <vector>

class TheMatrixAnime : public BaseAnime {
private:
    int maxPixels;
    std::vector<std::pair<int, int>> pixels;

public:
    TheMatrixAnime(int size, int maxPixels);
    void init() override;
    void step() override;
};

#endif
