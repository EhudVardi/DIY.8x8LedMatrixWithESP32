#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Models/Direction.h"
#include "Models/Point2D.h"
#include "Models/LinkedList.h"
#include "SnakeMatrix2D.h"
#include "Data/Utils/RandomGenerator.h"

enum class SnakeGameState {
    Initialized,
    Running,
    Ended
};

class SnakeGame {
private:
    Point2D tailPos;
    LinkedList snakeBody;
    SnakeMatrix2D boardMatrix;
    void PaintSnakeOnBoard();
    Point2D GetSnakeHeadPos();
    SnakeGameState gameState;
    float gameSpeedPercent;

public:
    SnakeGame(int width, int height);
    void InitGame();
    void StepGame();
    SnakeMatrix2D GetBoard() const;
    float GetGameSpeedPercent() const;
    void TurnSnake(Direction newDir);
};


#endif
