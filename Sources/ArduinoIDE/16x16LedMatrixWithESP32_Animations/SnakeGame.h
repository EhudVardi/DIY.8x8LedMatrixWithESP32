#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Structures\Direction.h"
#include "Structures\Point2D.h"
#include "Structures\LinkedList.h"

class SnakeGame {
private:
	Point2D tailPos;
	LinkedList snakeBody;
    
public:
  SnakeGame();
	void InitGame();
	void StepGame();
	void TurnSnake(bool clockWise);
	bool IsGameOver();
};


#endif
