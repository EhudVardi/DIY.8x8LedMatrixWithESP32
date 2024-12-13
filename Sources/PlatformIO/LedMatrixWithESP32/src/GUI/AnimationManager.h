#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "HAL/LedMatrixHandler.h"
#include "Animations/TheMatrix/TheMatrixAnime.h"
#include "Animations/BeatingHeart/BeatingHeartAnime.h"
#include "Animations/Spiral/SpiralAnime.h"
#include "Animations/Snake/SnakeInteractiveAnime.h"
#include "Animations/TextScroll/TextDisplayAnime.h"
#include "Animations/Tetris/TetrisInteractiveAnime.h"

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
