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

}
