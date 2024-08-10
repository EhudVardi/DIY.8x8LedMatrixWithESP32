#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include "Structures\Direction.h"
#include "Structures\Point2D.h"
#include "Structures\LinkedList.h"
#include "Structures\Matrix2D.h"

class SnakeGame {
private:
	Point2D tailPos;
	LinkedList snakeBody;
	Matrix2D boardMatrix;
	
	void PaintSnakeOnBoard();
	
	Point2D GetSnakeHeadPos();
	
	bool IsHeadOutOfBounds(Point2D headPos);
	bool IsHeadCollideWithBody(Point2D headPos);
	
public:
	SnakeGame(int width, int height);
	void InitGame();
	void StepGame();
	Matrix2D GetBoard() const;
	void TurnSnake(bool clockWise);
	bool IsGameOver();
};


#endif
