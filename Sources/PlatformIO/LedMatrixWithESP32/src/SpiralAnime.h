#ifndef SPIRALANIME_H
#define SPIRALANIME_H

#include "BaseInteractiveAnime.h"

enum Dir {
    Down = 0,
    Left = 1,
    Up = 2,
    Right = 3
};

class SpiralAnime : public BaseInteractiveAnime {
public:
    SpiralAnime(int size);
    void init() override;
    void step() override;
    void SetInputHandlers() override;

private:
    enum Dir stepDir;
    int8_t currTrailLength;
    int8_t currTrailStep;
    int8_t currRowIdx;
    int8_t currColIdx;
    bool trailInOrOut;
};

#endif  // SPIRALANIME_H
