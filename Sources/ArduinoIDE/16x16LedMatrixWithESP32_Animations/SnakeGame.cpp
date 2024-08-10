#include "SnakeGame.h"

SnakeGame::SnakeGame(int width, int height) 
	: boardMatrix(width, height){ }

void SnakeGame::InitGame(){
	//// init position of the snake tail
	//tailPos.x = boardMatrix.GetWidth()/2;
	//tailPos.y = boardMatrix.GetHeight()/2;
	//// init body of the snake - one section
	//snakeBody.append(L, 2);
	
	/*// create example 1
	tailPos.x = 10;
	tailPos.y = 2;
	snakeBody.append(L, 4);
	snakeBody.append(U, 1);
	snakeBody.append(L, 2);
	snakeBody.append(U, 3);
	snakeBody.append(R, 3);
	snakeBody.append(D, 1);*/
  	// create example 2
	tailPos.x = 2;
	tailPos.y = 2;
	snakeBody.append(R, 9);
	snakeBody.append(U, 2);	
  snakeBody.append(L, 8);
	snakeBody.append(U, 2);
	snakeBody.append(R, 7);
	snakeBody.append(U, 2);
  snakeBody.append(L, 6);
	snakeBody.append(U, 2);
	snakeBody.append(R, 5);
	snakeBody.append(U, 2);
  snakeBody.append(L, 3);
  // paint current snake on the board
  PaintSnakeOnBoard();
}

void SnakeGame::StepGame(){
	//// move the snake and update its body
  // get snake head and tail sections
	ListNode* snakeTail = snakeBody.getHead();
	ListNode* snakeHead = snakeBody.getTail();
  // clear the matrix cell of the old tail end of the snake
  boardMatrix.ClearCell(tailPos.x, tailPos.y); 
  // move the tail one step
	tailPos.Move(snakeTail->dir, 1);
  // update snake head and tail sections, trim tail section if finished
	snakeTail->length--;
	snakeHead->length++;
	if (snakeTail->length == 0)
		snakeBody.trimHead();
  // set the matrix cell of the new head of the snake
	Point2D headPos = GetSnakeHeadPos();
  boardMatrix.SetBodyCell(headPos.x, headPos.y); 
	
	//// check snake health (out of bounds or collide with body)
	if (IsHeadOutOfBounds(headPos) || IsHeadCollideWithBody(headPos)) {
		//TODO: endgame
		//TODO: IsHeadCollideWithBody, using the matrix instead of the body struct 
	}
}

Matrix2D SnakeGame::GetBoard() const {
	return boardMatrix;
}

void SnakeGame::PaintSnakeOnBoard() {
	// clear the matrix
	boardMatrix.Clear();
	// paint the snake body
	Point2D travelPos(tailPos.x, tailPos.y);
	boardMatrix.SetBodyCell(travelPos.x, travelPos.y); // paint first tail
	ListNode* travelNode = snakeBody.getHead();
	while (travelNode){
		for (int i=0; i< travelNode->length; i++) {
			travelPos.Move(travelNode->dir, 1);
			boardMatrix.SetBodyCell(travelPos.x, travelPos.y);
		}
		travelNode = travelNode->next;
	}
}


Point2D SnakeGame::GetSnakeHeadPos(){
	Point2D snakeHeadPos(tailPos.x, tailPos.y);
	ListNode* travelNode = snakeBody.getHead();
	while (travelNode){
		snakeHeadPos.Move(travelNode->dir, travelNode->length);
		travelNode = travelNode->next;
	}
	return snakeHeadPos;
}

bool SnakeGame::IsHeadOutOfBounds(Point2D headPos){
	return boardMatrix.IsPointOutOfBounds(headPos);
}

bool SnakeGame::IsHeadCollideWithBody(Point2D headPos){
	Point2D travelPos(tailPos.x, tailPos.y);
	ListNode* travelNode = snakeBody.getHead();
	while (travelNode->next){
		switch (travelNode->dir) {
			case L: {
				if (headPos.y == travelPos.y && 
					headPos.x <= travelPos.x && 
					headPos.x >= (travelPos.x - travelNode->length))
						return true;
			}
			case R: {
				if (headPos.y == travelPos.y && 
					headPos.x >= travelPos.x && 
					headPos.x <= (travelPos.x + travelNode->length))
						return true;
			}
			case D: {
				if (headPos.x == travelPos.x && 
					headPos.y <= travelPos.y && 
					headPos.y >= (travelPos.y - travelNode->length))
						return true;
			}
			case U: {
				if (headPos.x == travelPos.x && 
					headPos.y >= travelPos.y && 
					headPos.y <= (travelPos.y + travelNode->length))
						return true;
			}
		}
		travelPos.Move(travelNode->dir, travelNode->length);
		travelNode = travelNode->next;
	}
	return false;
}



bool SnakeGame::IsGameOver(){
	
	return false;
}


