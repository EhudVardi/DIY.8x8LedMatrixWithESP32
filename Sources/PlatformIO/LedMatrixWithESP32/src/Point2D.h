#ifndef POINT2D_H
#define POINT2D_H

#include "Direction.h"

class Point2D {
public:
  int x, y;

  Point2D(int x = 0, int y = 0)
    : x(x), y(y) {}

  void Move(Direction dir, int length);
  bool IsEqual(Point2D p2);
  //void Print();
};

#endif
