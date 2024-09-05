#include "TetrisInteractiveAnime.h"

TetrisInteractiveAnime::TetrisInteractiveAnime(int size)
  : BaseInteractiveAnime(size), game(size, size) {
  stepDuration = 10;
}

void TetrisInteractiveAnime::init() {
  game.InitGame();
  previousMillis = 0;
}

void TetrisInteractiveAnime::step() {

  // step the game if its time
  unsigned long currentMillis = millis();
  if (currentMillis - TetrisInteractiveAnime::previousMillis >= TetrisInteractiveAnime::getGameStepDuration()) {
    previousMillis = currentMillis;
    game.StepGame();
  }

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
    game.FinalizeTetrimino();
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

int TetrisInteractiveAnime::getGameStepDuration() {
  return stepDuration * ((1 - durationDiv) * game.GetGameSpeedPercent() + durationDiv);
}
