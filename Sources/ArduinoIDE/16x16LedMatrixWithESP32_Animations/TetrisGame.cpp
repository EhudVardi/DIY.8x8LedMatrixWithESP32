#include "TetrisGame.h"

TetrisGame::TetrisGame(int width, int height)
  : boardMatrix(width, height), currentTetrimino(nullptr), gameState(TetrisGameState::Initialized), gameSpeedPercent(0.0f) {
  InitTetriminoPool();
}

void TetrisGame::InitTetriminoPool() {
  tetriminoPool = {
    Tetrimino({
                { { Point2D(0, 0), Point2D(1, 0), Point2D(0, 1), Point2D(1, 1) } }  // Square has one rotation state
              },
              Point2D(boardMatrix.GetWidth() / 2, 1)),
    Tetrimino({ { { Point2D(0, 0), Point2D(-1, 0), Point2D(1, 0), Point2D(2, 0) } },  // Line has two rotation states
                { { Point2D(0, 0), Point2D(0, -1), Point2D(0, 1), Point2D(0, 2) } } },
              Point2D(boardMatrix.GetWidth() / 2, 1)),
    Tetrimino({ { { Point2D(0, 0), Point2D(0, 1), Point2D(-1, 0), Point2D(1, 0) } },  // T-Shape has four rotation states
                { { Point2D(0, 0), Point2D(0, -1), Point2D(1, 0), Point2D(0, 1) } },
                { { Point2D(0, 0), Point2D(0, -1), Point2D(-1, 0), Point2D(1, 0) } },
                { { Point2D(0, 0), Point2D(0, -1), Point2D(-1, 0), Point2D(0, 1) } } },
              Point2D(boardMatrix.GetWidth() / 2, 1)),
    Tetrimino({ { { Point2D(0, 0), Point2D(0, -1), Point2D(0, 1), Point2D(-1, 1) } },  // L-Shape has four rotation states
                { { Point2D(0, 0), Point2D(-1, 0), Point2D(1, 0), Point2D(1, 1) } },
                { { Point2D(0, 0), Point2D(0, 1), Point2D(0, -1), Point2D(1, -1) } },
                { { Point2D(0, 0), Point2D(1, 0), Point2D(-1, 0), Point2D(-1, -1) } } },
              Point2D(boardMatrix.GetWidth() / 2, 1)),
    Tetrimino({ { { Point2D(0, 0), Point2D(0, -1), Point2D(0, 1), Point2D(1, 1) } },  // L-Shape (reversed) has four rotation states
                { { Point2D(0, 0), Point2D(-1, 0), Point2D(1, 0), Point2D(1, -1) } },
                { { Point2D(0, 0), Point2D(0, 1), Point2D(0, -1), Point2D(-1, -1) } },
                { { Point2D(0, 0), Point2D(1, 0), Point2D(-1, 0), Point2D(-1, 1) } } },
              Point2D(boardMatrix.GetWidth() / 2, 1))
    // Add other shapes similarly
  };
}

void TetrisGame::InitGame() {
  SpawnNewTetrimino();
  gameState = TetrisGameState::Running;
}

void TetrisGame::SpawnNewTetrimino() {
  int index = RandomGenerator::nextInt(0, tetriminoPool.size());
  currentTetrimino = new Tetrimino(tetriminoPool[index]);
}

void TetrisGame::StepGame() {
  if (gameState != TetrisGameState::Running)
    return;

  currentTetrimino->Move(U);  // Move the Tetrimino down
  if (boardMatrix.IsCollision(*currentTetrimino)) {
    currentTetrimino->Move(D);  // Move it back up
    PlaceTetrimino();
    int filledRowsCount = ClearFilledRows();
    gameSpeedPercent += (gameSpeedPercentStep * filledRowsCount);
    if (gameSpeedPercent >= 1.0) {
      gameState = TetrisGameState::Ended;
      return;
    }
    SpawnNewTetrimino();
    if (boardMatrix.IsCollision(*currentTetrimino)) {
      gameState = TetrisGameState::Ended;
    }
  }
}

void TetrisGame::PlaceTetrimino() {
  boardMatrix.AddTetrimino(*currentTetrimino);
  delete currentTetrimino;
  currentTetrimino = nullptr;
}

int TetrisGame::ClearFilledRows() {

  int filledRows = 0;
  int height = boardMatrix.GetHeight();
  int width = boardMatrix.GetWidth();

  // Vector to hold rows that are not cleared
  std::vector<std::vector<int>> newBoard(height, std::vector<int>(width, 0));

  // Start scanning from the bottom of the board
  int currentRow = height - 1;

  for (int y = height - 1; y >= 0; --y) {
    bool isRowFilled = true;
    for (int x = 0; x < width; ++x) {
      if (boardMatrix.Get(x, y) == 0) {
        isRowFilled = false;
        break;
      }
    }

    if (isRowFilled) {
      filledRows++;
      // Skip this row; it's filled and will be removed
      continue;
    } else {
      // Copy the current row to the newBoard
      for (int x = 0; x < width; ++x) {
        newBoard[currentRow][x] = boardMatrix.Get(x, y);
      }
      --currentRow;  // Move to the next row up in the newBoard
    }
  }

  // Write the newBoard back to the boardMatrix
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      boardMatrix.Set(x, y, newBoard[y][x]);
    }
  }

  return filledRows;
}


TetrisMatrix2D TetrisGame::GetBoard() const {
  return boardMatrix;
}

Tetrimino* TetrisGame::GetCurrTetrimino() const {
  return currentTetrimino;
}

float TetrisGame::GetGameSpeedPercent() const {
  return gameSpeedPercent;
}

void TetrisGame::MoveTetrimino(Direction dir) {
  currentTetrimino->Move(dir);
  if (boardMatrix.IsCollision(*currentTetrimino)) {
    currentTetrimino->Move(Turn(Turn(dir, CWISE), CWISE));  // Move back if collision
  }
}

void TetrisGame::RotateTetrimino(bool clockWise) {
  currentTetrimino->Rotate(clockWise);
  if (boardMatrix.IsCollision(*currentTetrimino)) {
    currentTetrimino->Rotate(!clockWise);  // Rotate back if collision
  }
}
