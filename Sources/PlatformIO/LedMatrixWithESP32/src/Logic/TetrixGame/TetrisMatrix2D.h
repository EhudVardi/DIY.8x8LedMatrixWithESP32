#ifndef TETRIS_MATRIX2D_H
#define TETRIS_MATRIX2D_H

#include "Models/Matrix2D.h"
#include "Tetrimino.h"
#include "Models/Point2D.h"
#include <vector>

class TetrisMatrix2D : public Matrix2D<int> {
public:
    TetrisMatrix2D(int width, int height);

    bool IsRowFilled(int row) const;
    void Clear();
    void ClearRow(int row);
    void AddTetrimino(const Tetrimino& tetrimino);
    bool IsCollision(const Tetrimino& tetrimino) const;
};

#endif  // TETRIS_MATRIX2D_H
