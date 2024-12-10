#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "Point2D.h"
#include "Direction.h"
#include <vector>

class Tetrimino {
private:
    std::vector<std::vector<Point2D>> shapes; // All possible shapes of the Tetrimino
    int currentShapeIndex; // Index of the current shape
    Point2D position; // Absolute position of the Tetrimino

public:
    Tetrimino(const std::vector<std::vector<Point2D>>& shapes, const Point2D& startPos);

    void Move(Direction dir);
    void Rotate(bool clockWise);
    std::vector<Point2D> GetBlocks() const;
    Point2D GetPosition() const;
    void SetPosition(const Point2D& newPos);
    std::vector<Point2D> GetAbsoluteBlocks() const; // Get absolute block positions
};

#endif