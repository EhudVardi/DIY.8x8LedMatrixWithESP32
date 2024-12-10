#include "SnakeMatrix2D.h"

SnakeMatrix2D::SnakeMatrix2D(int w, int h)
    : Matrix2D(w, h) {
}

void SnakeMatrix2D::Clear() {
    MatrixElement emptyElement = {};
    for (int i = 0; i < GetHeight(); ++i) {
        for (int j = 0; j < GetWidth(); ++j) {
            Set(j, i, emptyElement);  // Clear all cells to the empty element
        }
    }
}

void SnakeMatrix2D::SetBodyCell(int x, int y) {
    if (!IsPointOutOfBounds(x, y)) {
        MatrixElement element = Get(x, y);
        element.body = 1;
        Set(x, y, element);
    }
}

void SnakeMatrix2D::SetFoodCell(int x, int y) {
    if (!IsPointOutOfBounds(x, y)) {
        MatrixElement element = Get(x, y);
        element.food = 1;
        Set(x, y, element);
    }
}

void SnakeMatrix2D::ClearCell(int x, int y) {
    if (!IsPointOutOfBounds(x, y)) {
        MatrixElement element = Get(x, y);
        element.value = 0;
        Set(x, y, element);
    }
}

bool SnakeMatrix2D::IsBodyCell(int x, int y) const {
    return !IsPointOutOfBounds(x, y) && Get(x, y).body;
}

bool SnakeMatrix2D::IsFoodCell(int x, int y) const {
    return !IsPointOutOfBounds(x, y) && Get(x, y).food;
}

bool SnakeMatrix2D::IsClearCell(int x, int y) const {
    return !IsPointOutOfBounds(x, y) && Get(x, y).value == 0;
}
