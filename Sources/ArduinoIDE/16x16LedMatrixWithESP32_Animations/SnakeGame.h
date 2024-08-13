#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Direction.h"
#include "Point2D.h"
#include "LinkedList.h"
#include "Matrix2D.h"
#include "RandomGenerator.h"

enum GameState { Initialized,
                 Running,
                 Ended };

class SnakeGame {
private:
  Point2D tailPos;
  LinkedList snakeBody;
  Matrix2D boardMatrix;
  void PaintSnakeOnBoard();
  Point2D GetSnakeHeadPos();
  GameState gameState;
  float gameSpeedPercent;

public:
  SnakeGame(int width, int height);
  void InitGame();
  void StepGame();
  Matrix2D GetBoard() const;
  float GetGameSpeedPercent() const;
  void TurnSnake(Direction newDir);
};


#endif
