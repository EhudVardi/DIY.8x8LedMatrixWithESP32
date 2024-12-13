#ifndef STARTRAVELANIME_H
#define STARTRAVELANIME_H

#include "../BaseInteractiveAnime.h"
#include <vector>

struct Star {
    float x, y, z;
};

class StarTravelAnime : public BaseInteractiveAnime {
public:
    StarTravelAnime(int starCount, int matrixSize);
    void init(LedMatrixHandler* ledMatrixHandler) override;
    void step(LedMatrixHandler* ledMatrixHandler) override;
    void SetInputHandlers() override;

private:
    void respawnStar(Star& star);
    std::vector<Star> stars;
    int matrixSize;
    float speed;
    float fieldOfView;
};

#endif  // STARTRAVELANIME_H
