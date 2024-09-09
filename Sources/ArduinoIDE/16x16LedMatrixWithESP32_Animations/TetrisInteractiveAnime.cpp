#include "TetrisInteractiveAnime.h"

TetrisInteractiveAnime::TetrisInteractiveAnime(int size)
  : BaseInteractiveAnime(size), game(size, size) {
  stepDuration = 10;
  SetInputHandlers();
}

void TetrisInteractiveAnime::init() {
  game.InitGame();
  previousGameStepMillis = 0;
  previousMoveStepMillis = 0;
}

void TetrisInteractiveAnime::step() {

  unsigned long currentMillis = millis();
  // step the game if its time
  if (currentMillis - TetrisInteractiveAnime::previousGameStepMillis >= TetrisInteractiveAnime::getGameStepDuration()) {
    previousGameStepMillis = currentMillis;
    game.StepGame();
  }
  // continous move of tetrimino if enabled
  if (currentMillis - TetrisInteractiveAnime::previousMoveStepMillis >= TetrisInteractiveAnime::getMoveStepDuration()) {
    previousMoveStepMillis = currentMillis;
    if (isMovingTetrimino)
      game.MoveTetrimino(tetriminoMoveDirection);
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
  RegisterInputHandler(0, [this](bool isSet) {
    if (isSet)
      game.FinalizeTetrimino();
  });
  RegisterInputHandler(1, [this](bool isSet) {
    if (isSet)
      game.RotateTetrimino(false);
  });
  RegisterInputHandler(2, [this](bool isSet) {
    if (isSet) {
      isMovingTetrimino = true;
      tetriminoMoveDirection = L;
    } else isMovingTetrimino = false;
  });
  RegisterInputHandler(3, [this](bool isSet) {
    if (isSet) {
      isMovingTetrimino = true;
      tetriminoMoveDirection = R;
    } else isMovingTetrimino = false;
  });
}

int TetrisInteractiveAnime::getGameStepDuration() {
  return stepDuration * ((1 - durationDiv) * game.GetGameSpeedPercent() + durationDiv);
}

int TetrisInteractiveAnime::getMoveStepDuration() {
  return stepDuration * 10;
}
