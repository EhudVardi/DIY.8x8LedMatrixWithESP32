#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "Point2D.h"
#include "Direction.h"
#include <vector>

class Tetrimino {
private:
  std::vector<Point2D> blocks;  // Relative positions of blocks
  Point2D position;             // Absolute position of the Tetrimino
  Direction rotation;

  // Helper function to rotate a point around the origin
  Point2D RotatePoint(const Point2D& point, bool clockWise) const;

public:
  Tetrimino(const std::vector<Point2D>& shape, const Point2D& startPos);

  void Move(Direction dir);
  void Rotate(bool clockWise);
  std::vector<Point2D> GetBlocks() const;
  Point2D GetPosition() const;
  void SetPosition(const Point2D& newPos);

  // New method to get absolute block positions
  std::vector<Point2D> GetAbsoluteBlocks() const;
};

#endif
