#include "Tetrimino.h"

Tetrimino::Tetrimino(const std::vector<std::vector<Point2D>>& shapes, const Point2D& startPos)
    : shapes(shapes), currentShapeIndex(0), position(startPos) {
}

void Tetrimino::Move(Direction dir) {
    position.Move(dir, 1);  // Move the position of the Tetrimino
}

void Tetrimino::Rotate(bool clockWise) {
    if (clockWise) {
        currentShapeIndex = (currentShapeIndex + 1) % shapes.size();
    }
    else {
        currentShapeIndex = (currentShapeIndex - 1 + shapes.size()) % shapes.size();
    }
}

std::vector<Point2D> Tetrimino::GetBlocks() const {
    return shapes[currentShapeIndex];
}

Point2D Tetrimino::GetPosition() const {
    return position;
}

void Tetrimino::SetPosition(const Point2D& newPos) {
    position = newPos;
}

std::vector<Point2D> Tetrimino::GetAbsoluteBlocks() const {
    std::vector<Point2D> absoluteBlocks;
    for (const auto& block : GetBlocks()) {
        absoluteBlocks.emplace_back(block.x + position.x, block.y + position.y);
    }
    return absoluteBlocks;
}