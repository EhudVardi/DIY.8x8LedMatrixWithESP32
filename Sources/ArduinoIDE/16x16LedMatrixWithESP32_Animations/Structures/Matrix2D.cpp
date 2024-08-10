#include "Matrix2D.h"

// Constructor implementation
Matrix2D::Matrix2D(int w, int h) 
    : width(w), height(h), matrix(h, std::vector<MatrixElement>(w)) {}

int Matrix2D::GetWidth() { return width; }
int Matrix2D::GetHeight()  { return height; }

bool Matrix2D::IsPointOutOfBounds(Point2D point) {
	return (point.x < 0 || point.x >= width || 
			point.y < 0 || point.y >= height);
}
	
	
void Matrix2D::Clear() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            matrix[i][j].value = 0;  // Clear each element's value to 0
        }
    }
}

void Matrix2D::Set(int x, int y, const MatrixElement& value) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        matrix[y][x] = value;  // Set the value at the specified position
    }
}
MatrixElement Matrix2D::Get(int x, int y) const {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return matrix[y][x];  // Return the value at the specified position
    } else {
        return MatrixElement{};  // Return a default value if the position is out of bounds
    }
}

void Matrix2D::SetBodyCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        matrix[y][x].value = 1;
    }
}
void Matrix2D::SetFoodCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        matrix[y][x].value = 2;
    }
}
void Matrix2D::ClearCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        matrix[y][x].value = 0;
    }
}

bool Matrix2D::IsBodyCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return matrix[y][x].body;
    }
}
bool Matrix2D::IsFoodCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return matrix[y][x].food;
    }
}
bool Matrix2D::IsClearCell(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return (!matrix[y][x].value);
    }
}
