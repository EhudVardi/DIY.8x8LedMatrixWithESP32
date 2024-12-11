#ifndef TETRIS_INTERACTIVE_ANIME_H
#define TETRIS_INTERACTIVE_ANIME_H

#include "BaseInteractiveAnime.h"
#include "TetrisGame.h"

class TetrisInteractiveAnime : public BaseInteractiveAnime {
private:
    TetrisGame game;

    const float durationDiv = 50;
    int getGameStepDuration();
    unsigned long previousGameStepMillis = 0;

    bool isMovingTetrimino = false;
    Direction tetriminoMoveDirection = L;
    int getMoveStepDuration();
    unsigned long previousMoveStepMillis = 0;

public:
    TetrisInteractiveAnime(int size);
    void init(LedMatrixHandler* ledMatrixHandler) override;
    void step(LedMatrixHandler* ledMatrixHandler) override;
    void SetInputHandlers() override;
};

#endif
