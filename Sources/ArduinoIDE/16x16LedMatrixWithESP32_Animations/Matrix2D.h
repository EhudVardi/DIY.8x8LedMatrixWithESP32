#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <vector>

#include "Point2D.h"

// Struct to represent a matrix element
struct MatrixElement {
  union {
    int value;
    struct {
      unsigned int body : 1;
      unsigned int food : 1;
      unsigned int UNUSED : 6;
    };
  };
};

// Class to represent a 2D matrix
class Matrix2D {
private:
  int width;
  int height;
  std::vector<std::vector<MatrixElement>> matrix;

public:
  Matrix2D(int w, int h);  // Constructor to initialize matrix dimensions

  int GetWidth();
  int GetHeight();

  bool IsPointOutOfBounds(Point2D point);

  void Clear();  // Function to clear all values in the matrix
  void Set(int x, int y, const MatrixElement& value);
  MatrixElement Get(int x, int y) const;

  void SetBodyCell(int x, int y);
  void SetFoodCell(int x, int y);
  void ClearCell(int x, int y);

  bool IsBodyCell(int x, int y);
  bool IsFoodCell(int x, int y);
  bool IsClearCell(int x, int y);
};

#endif  // MATRIX2D_H
