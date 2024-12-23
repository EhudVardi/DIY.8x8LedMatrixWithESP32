#include "SnakeInteractiveAnime.h"

SnakeInteractiveAnime::SnakeInteractiveAnime(int size)
    : BaseInteractiveAnime(), game(size, size) {
    stepDuration = 500;
    SetInputHandlers();
}

void SnakeInteractiveAnime::init(LedMatrixHandler* ledMatrixHandler) {
    game.InitGame();
}

void SnakeInteractiveAnime::step(LedMatrixHandler* ledMatrixHandler) {
    // step the game
    game.StepGame();
    // update display matrix from game board
    ledMatrixHandler->clearMatrix();
    SnakeMatrix2D gameBoard = game.GetBoard();
    for (int i = 0; i < gameBoard.GetWidth(); i++) {
        for (int j = 0; j < gameBoard.GetHeight(); j++) {
            if (!gameBoard.IsClearCell(i, j))
                ledMatrixHandler->setPixel(i, j, true);
        }
    }
}

void SnakeInteractiveAnime::SetInputHandlers() {
    RegisterInputHandler(0, [this](bool isSet) {
        if (isSet)
            game.TurnSnake(U);
    });
    RegisterInputHandler(1, [this](bool isSet) {
        if (isSet)
            game.TurnSnake(D);
    });
    RegisterInputHandler(2, [this](bool isSet) {
        if (isSet)
            game.TurnSnake(L);
    });
    RegisterInputHandler(3, [this](bool isSet) {
        if (isSet)
            game.TurnSnake(R);
    });
}

int SnakeInteractiveAnime::getStepDuration() {
    // return a modified step duration, according to the game current speed percent
    // at 0.0 the step duration should be full - baseDuration
    // at 1.0 the step duration should be completely divided with the local const "durationDiv"
    // find the linear equation coefs a and b
    // finalStepDuration = a*(gameSpeedPercent)+b
    // -> finalStepDuration = baseDuration*(gameSpeedPercent*((1-durationDiv)/durationDiv)+1)
    // also make sure the minimum finalStepDuration value will be at least 1 (using max(1,..))
    return max(1, (int)(stepDuration * (game.GetGameSpeedPercent() * durationCoef + 1.0)));
}
