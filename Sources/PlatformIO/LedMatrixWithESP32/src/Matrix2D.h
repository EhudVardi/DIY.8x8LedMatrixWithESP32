#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <vector>
#include "Point2D.h"

template<typename T>
class Matrix2D {
private:
  int width;
  int height;
  std::vector<std::vector<T>> matrix;

public:
  Matrix2D(int w, int h);  // Constructor to initialize matrix dimensions

  int GetWidth() const;
  int GetHeight() const;

  bool IsPointOutOfBounds(int x, int y) const;
  bool IsPointOutOfBounds(Point2D p) const;

  void Clear(const T& value);  // Function to clear all values in the matrix
  void Set(int x, int y, const T& value);
  T Get(int x, int y) const;
};

// Inline implementation of generic functions

template<typename T>
Matrix2D<T>::Matrix2D(int w, int h)
  : width(w), height(h), matrix(h, std::vector<T>(w)) {}

template<typename T>
int Matrix2D<T>::GetWidth() const {
  return width;
}

template<typename T>
int Matrix2D<T>::GetHeight() const {
  return height;
}

template<typename T>
bool Matrix2D<T>::IsPointOutOfBounds(int x, int y) const {
  return (x < 0 || x >= width || y < 0 || y >= height);
}

template<typename T>
bool Matrix2D<T>::IsPointOutOfBounds(Point2D p) const {
  return (p.x < 0 || p.x >= width || p.y < 0 || p.y >= height);
}

template<typename T>
void Matrix2D<T>::Clear(const T& value) {
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      matrix[i][j] = value;
    }
  }
}

template<typename T>
void Matrix2D<T>::Set(int x, int y, const T& value) {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    matrix[y][x] = value;
  }
}

template<typename T>
T Matrix2D<T>::Get(int x, int y) const {
  if (x >= 0 && x < width && y >= 0 && y < height) {
    return matrix[y][x];
  } else {
    return T{};
  }
}

#endif  // MATRIX2D_H
