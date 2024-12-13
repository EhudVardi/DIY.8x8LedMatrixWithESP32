#ifndef SNAKEMATRIX2D_H
#define SNAKEMATRIX2D_H

#include "Models/Matrix2D.h"

// Struct to represent a matrix element for the Snake game
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

// Class to represent a 2D matrix specifically for the Snake game
class SnakeMatrix2D : public Matrix2D<MatrixElement> {
public:
    SnakeMatrix2D(int w, int h);  // Constructor

    void Clear();

    void SetBodyCell(int x, int y);
    void SetFoodCell(int x, int y);
    void ClearCell(int x, int y);

    bool IsBodyCell(int x, int y) const;
    bool IsFoodCell(int x, int y) const;
    bool IsClearCell(int x, int y) const;
};

#endif  // SNAKEMATRIX2D_H
