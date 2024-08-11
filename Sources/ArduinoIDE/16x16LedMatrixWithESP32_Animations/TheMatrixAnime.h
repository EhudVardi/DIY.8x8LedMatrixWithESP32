#ifndef THE_MATRIX_ANIME_H
#define THE_MATRIX_ANIME_H

#include "BaseInteractiveAnime.h"
#include <vector>

class TheMatrixAnime : public BaseInteractiveAnime {
private:
    int maxPixels;
    std::vector<std::pair<int, int>> pixels;

public:
    TheMatrixAnime(int size, int maxPixels);
    void init() override;
    void step() override;
};

#endif
