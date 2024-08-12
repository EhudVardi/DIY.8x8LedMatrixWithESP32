#ifndef BEATINGHEARTANIME_H
#define BEATINGHEARTANIME_H

#include "BaseInteractiveAnime.h"

class BeatingHeartAnime : public BaseInteractiveAnime {
public:
    BeatingHeartAnime(int matrixSize);
    void init() override;
    void step() override;
    void SetInputHandlers() override;

private:
    void drawHeart(const uint8_t* heart, int size);
    const uint8_t smallHeart[5][5] = { 
        {0, 1, 0, 1, 0},
        {1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1},
        {0, 1, 1, 1, 0},
        {0, 0, 1, 0, 0}
    };
    const uint8_t mediumHeart[7][7] = {
        {0, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 0, 0}
    };
    const uint8_t largeHeart[9][9] = {
        {0, 1, 0, 0, 0, 0, 1, 0, 0},
        {1, 1, 1, 0, 0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 0, 0, 0}
    };
    int8_t stepCount;
    bool direction;
};

#endif // BEATINGHEARTANIME_H
