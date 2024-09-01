#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "Tetrimino.h"
#include "TetrisMatrix2D.h"
#include "RandomGenerator.h"

enum class TetrisGameState { Initialized,
                             Running,
                             Ended };

class TetrisGame {
private:
  TetrisMatrix2D boardMatrix;
  Tetrimino* currentTetrimino;
  TetrisGameState gameState;
  float gameSpeedPercent;
  const float gameSpeedPercentStep = 0.05;

  void SpawnNewTetrimino();
  void PlaceTetrimino();
  int ClearFilledRows();

public:
  TetrisGame(int width, int height);
  void InitGame();
  void StepGame();
  TetrisMatrix2D GetBoard() const;
  Tetrimino* GetCurrTetrimino() const;
  float GetGameSpeedPercent() const;
  void MoveTetrimino(Direction dir);
  void RotateTetrimino(bool clockWise);
};

#endif
