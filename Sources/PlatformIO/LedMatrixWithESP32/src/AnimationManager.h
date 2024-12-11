#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "BaseInteractiveAnime.h"
#include "LedMatrixHandler.h"
#include "TheMatrixAnime.h"
#include "BeatingHeartAnime.h"
#include "SpiralAnime.h"
#include "SnakeInteractiveAnime.h"
#include "TextDisplayAnime.h"
#include "TetrisInteractiveAnime.h"

#include <vector>

class AnimationManager {
public:
    AnimationManager(int screenSize);
    void init(LedMatrixHandler* ledMatrixHandler);
    BaseInteractiveAnime* getCurrentAnime();
    void skipToNextAnime(LedMatrixHandler* ledMatrixHandler);
    void initCurrAnime(LedMatrixHandler* ledMatrixHandler);

private:
    int currAnimeIndex;
    std::vector<BaseInteractiveAnime*> animations;
    BaseInteractiveAnime* animation;
};

#endif
