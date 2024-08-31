#include "SnakeInteractiveAnime.h"

SnakeInteractiveAnime::SnakeInteractiveAnime(int size)
  : BaseInteractiveAnime(size), game(size, size) {
  stepDuration = 500;
}

void SnakeInteractiveAnime::init() {
  game.InitGame();
}

void SnakeInteractiveAnime::step() {
  // step the game
  game.StepGame();
  // update display matrix from game board
  clearMatrix();
  SnakeMatrix2D gameBoard = game.GetBoard();
  for (int i = 0; i < gameBoard.GetWidth(); i++) {
    for (int j = 0; j < gameBoard.GetHeight(); j++) {
      if (!gameBoard.IsClearCell(i, j))
        setPixel(i, j, true);
    }
  }
}

void SnakeInteractiveAnime::SetInputHandlers() {
  inputHandlers[0] = [this]() {
    game.TurnSnake(U);
  };
  inputHandlers[1] = [this]() {
    game.TurnSnake(D);
  };
  inputHandlers[2] = [this]() {
    game.TurnSnake(L);
  };
  inputHandlers[3] = [this]() {
    game.TurnSnake(R);
  };
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
