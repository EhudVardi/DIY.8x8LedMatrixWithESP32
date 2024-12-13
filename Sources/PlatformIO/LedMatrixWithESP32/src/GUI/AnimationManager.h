#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "HAL/LedMatrixHandler.h"
#include "GUI/Animations/TheMatrix/TheMatrixAnime.h"
#include "GUI/Animations/BeatingHeart/BeatingHeartAnime.h"
#include "GUI/Animations/Spiral/SpiralAnime.h"
#include "GUI/Animations/Snake/SnakeInteractiveAnime.h"
#include "GUI/Animations/TextScroll/TextDisplayAnime.h"
#include "GUI/Animations/Tetris/TetrisInteractiveAnime.h"

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
