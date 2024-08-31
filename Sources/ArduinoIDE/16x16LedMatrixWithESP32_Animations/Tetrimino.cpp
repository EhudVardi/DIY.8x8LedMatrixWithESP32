#include "Tetrimino.h"

Tetrimino::Tetrimino(const std::vector<Point2D>& shape, const Point2D& startPos)
  : blocks(shape), position(startPos), rotation(Direction::D) {}

void Tetrimino::Move(Direction dir) {
  position.Move(dir, 1);  // Move the position of the Tetrimino
}

void Tetrimino::Rotate(bool clockWise) {
  Point2D origin = position;
  for (auto& block : blocks) {
    block = RotatePoint(block, clockWise);
  }
}

Point2D Tetrimino::RotatePoint(const Point2D& point, bool clockWise) const {
  int dx = point.x;
  int dy = point.y;

  if (clockWise) {
    return Point2D(-dy, dx);
  } else {
    return Point2D(dy, -dx);
  }
}

std::vector<Point2D> Tetrimino::GetBlocks() const {
  return blocks;
}

Point2D Tetrimino::GetPosition() const {
  return position;
}

void Tetrimino::SetPosition(const Point2D& newPos) {
  position = newPos;
}

std::vector<Point2D> Tetrimino::GetAbsoluteBlocks() const {
  std::vector<Point2D> absoluteBlocks;
  for (const auto& block : blocks) {
    absoluteBlocks.emplace_back(block.x + position.x, block.y + position.y);
  }
  return absoluteBlocks;
}
