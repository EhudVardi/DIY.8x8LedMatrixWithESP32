#ifndef SPIRALANIME_H
#define SPIRALANIME_H

#include "BaseAnime.h"

enum Direction {Down=0,Left=1,Up=2,Right=3};

class SpiralAnime : public BaseAnime {
public:
    SpiralAnime(int matrixSize);
    void init() override;
    void step() override;

private:
    enum Direction stepDirection;
    int8_t currTrailLength;
    int8_t currTrailStep;
    int8_t currRowIdx;
    int8_t currColIdx;
    bool trailInOrOut;
};

#endif // SPIRALANIME_H
