#include "TetrisInteractiveAnime.h"

TetrisInteractiveAnime::TetrisInteractiveAnime(int size)
  : BaseInteractiveAnime(size), game(size, size) {
  stepDuration = 500;
}

void TetrisInteractiveAnime::init() {
  game.InitGame();
}

void TetrisInteractiveAnime::step() {
  // step the game
  game.StepGame();
  // update display matrix from game board
  clearMatrix();
  TetrisMatrix2D gameBoard = game.GetBoard();
  for (int i = 0; i < gameBoard.GetWidth(); i++) {
    for (int j = 0; j < gameBoard.GetHeight(); j++) {
      setPixel(i, j, (bool)gameBoard.Get(i, j));
    }
  }
  Tetrimino* currTetrimino = game.GetCurrTetrimino();
  std::vector<Point2D> tetriBlocks = currTetrimino->GetAbsoluteBlocks();
  for (const auto& block : tetriBlocks) {
    setPixel(block.x, block.y, true);
  }
}

void TetrisInteractiveAnime::SetInputHandlers() {
  inputHandlers[0] = [this]() {
    game.RotateTetrimino(true);
  };
  inputHandlers[1] = [this]() {
    game.RotateTetrimino(false);
  };
  inputHandlers[2] = [this]() {
    game.MoveTetrimino(L);
  };
  inputHandlers[3] = [this]() {
    game.MoveTetrimino(R);
  };
}

int TetrisInteractiveAnime::getStepDuration() {
  // return a modified step duration, according to the game current speed percent
  // at 0.0 the step duration should be full - baseDuration
  // at 1.0 the step duration should be completely divided with the local const "durationDiv"
  // find the linear equation coefs a and b
  // finalStepDuration = a*(gameSpeedPercent)+b
  // -> finalStepDuration = baseDuration*(gameSpeedPercent*((1-durationDiv)/durationDiv)+1)
  // also make sure the minimum finalStepDuration value will be at least 1 (using max(1,..))
  return max(1, (int)(stepDuration * (game.GetGameSpeedPercent() * durationCoef + 1.0)));
}
