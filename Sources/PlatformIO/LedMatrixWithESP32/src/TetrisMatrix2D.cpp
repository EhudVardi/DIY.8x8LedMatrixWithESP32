#include "TetrisMatrix2D.h"

TetrisMatrix2D::TetrisMatrix2D(int width, int height)
  : Matrix2D<int>(width, height) {}

bool TetrisMatrix2D::IsRowFilled(int row) const {
  for (int x = 0; x < GetWidth(); x++) {
    if (Get(x, row) == 0)
      return false;
  }
  return true;
}

void TetrisMatrix2D::ClearRow(int row) {
  // Shift all rows above the cleared row down by one
  for (int y = row; y > 0; y--) {
    for (int x = 0; x < GetWidth(); x++) {
      Set(x, y, Get(x, y - 1));
    }
  }
  // Clear the top row
  for (int x = 0; x < GetWidth(); x++) {
    Set(x, 0, 0);
  }
}

void TetrisMatrix2D::AddTetrimino(const Tetrimino& tetrimino) {
  for (const auto& block : tetrimino.GetAbsoluteBlocks()) {
    if (!IsPointOutOfBounds(block)) {
      Set(block.x, block.y, 1);
    }
  }
}

bool TetrisMatrix2D::IsCollision(const Tetrimino& tetrimino) const {
  for (const auto& block : tetrimino.GetAbsoluteBlocks()) {
    if (IsPointOutOfBounds(block) || Get(block.x, block.y) != 0) {
      return true;
    }
  }
  return false;
}
