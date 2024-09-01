#include "TetrisGame.h"

TetrisGame::TetrisGame(int width, int height)
  : boardMatrix(width, height), currentTetrimino(nullptr), gameState(TetrisGameState::Initialized), gameSpeedPercent(0.0f) {}

void TetrisGame::InitGame() {
  SpawnNewTetrimino();
  gameState = TetrisGameState::Running;
}

void TetrisGame::SpawnNewTetrimino() {
  static std::vector<std::vector<Point2D>> shapes = {
    { Point2D(0, 0), Point2D(1, 0), Point2D(0, 1), Point2D(1, 1) },       // Square
    { Point2D(0, 0), Point2D(-1, 0), Point2D(1, 0), Point2D(2, 0) },      // Line
    { Point2D(0, 0), Point2D(0, -1), Point2D(1, 0), Point2D(0, 1) },      // T-Shape
    { Point2D(0, 0), Point2D(0, -1), Point2D(-1, -1), Point2D(0, 1) },  // L-Shape
    { Point2D(0, 0), Point2D(0, -1), Point2D(1, -1), Point2D(0, 1) },    // L-Shape mirrored
  };

  int index = RandomGenerator::nextInt(0, shapes.size());
  Point2D startPos(boardMatrix.GetWidth() / 2, 1);  // Start position at the top center of the board
  currentTetrimino = new Tetrimino(shapes[index], startPos);
}

void TetrisGame::StepGame() {
  if (gameState != TetrisGameState::Running)
    return;

  currentTetrimino->Move(U);  // Move the Tetrimino down
  if (boardMatrix.IsCollision(*currentTetrimino)) {
    currentTetrimino->Move(D);  // Move it back up
    PlaceTetrimino();
    ClearFilledRows();
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
