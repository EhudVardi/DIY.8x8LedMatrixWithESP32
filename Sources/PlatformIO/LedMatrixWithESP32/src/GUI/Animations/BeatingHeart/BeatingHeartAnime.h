#ifndef BEATINGHEARTANIME_H
#define BEATINGHEARTANIME_H

#include <vector>
#include "../BaseInteractiveAnime.h"
#include "Data/Bitmaps/heartBitmaps.h"

class BeatingHeartAnime : public BaseInteractiveAnime {
public:
    BeatingHeartAnime(int size);
    void init(LedMatrixHandler* ledMatrixHandler) override;
    void step(LedMatrixHandler* ledMatrixHandler) override;
    void SetInputHandlers() override;

private:
    void drawHeart(LedMatrixHandler* ledMatrixHandler, const uint8_t* heart, int size);
    std::vector<const uint8_t(*)[12]> heartMatrices = {
      smallHeart,
      mediumHeart,
      largeHeart,
      extraLargeHeart,
      mediumHeart,
      largeHeart,
      extraLargeHeart,
      largeHeart,
      mediumHeart,
      smallHeart,
      smallHeart,
      smallHeart,
    };
    int8_t currHeartIndex;
};

#endif  // BEATINGHEARTANIME_H
