#include "SnakeGame.h"

SnakeGame::SnakeGame(int width, int height) 
	: boardMatrix(width, height), gameState(Initialized) { }

void SnakeGame::InitGame(){
	// init position of the snake tail
	tailPos.x = boardMatrix.GetWidth()/2;
	tailPos.y = boardMatrix.GetHeight()/2;
	// init body of the snake - one section
	snakeBody.append(L, 2);
	
	/*// create example 1
	tailPos.x = 10;
	tailPos.y = 2;
	snakeBody.append(L, 4);
	snakeBody.append(U, 1);
	snakeBody.append(L, 2);
	snakeBody.append(U, 3);
	snakeBody.append(R, 3);
	snakeBody.append(D, 1);*/
  /*// create example 2
	tailPos.x = 2;
	tailPos.y = 2;
	snakeBody.append(R, 9);
	snakeBody.append(U, 2);	
  snakeBody.append(L, 8);
	snakeBody.append(U, 2);
	snakeBody.append(R, 7);
	snakeBody.append(U, 6);
  snakeBody.append(L, 6);
  snakeBody.append(D, 1);*/
  // paint current snake on the board
  PaintSnakeOnBoard();
  gameState = Running;
}

void SnakeGame::StepGame(){
  if (gameState != Running)
    return;
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
  // check if the new snake head is out of bounds or if it collides with itself
	Point2D headPos = GetSnakeHeadPos();
  if (boardMatrix.IsPointOutOfBounds(headPos) || boardMatrix.IsBodyCell(headPos.x, headPos.y)) {
    gameState = Ended; // end the game and exit
    return;
  }
  // no collisions, set new head on the matrix and allow the game to continue
  boardMatrix.SetBodyCell(headPos.x, headPos.y); 
}

void SnakeGame::TurnSnake(Direction newDir) {
  //TODO: decide to turn the snake or not according its current direction and the snake head section length
  // allow to turn if new direction is adjecent to current snake head section direction (i.e., deny if its the same or opposite direction, else allow)
  // allow to turn only if the snake head section length is not zero (this signals that previous input has turned the snake but step did not occured yet)
  // to turn, simply append a new section to the snake head with a length of zero and with the new direction
  ListNode* snakeHead = snakeBody.getTail();
  if (snakeHead->length > 0 && IsDirectionsAdjacent(snakeHead->dir, newDir)) {
    snakeBody.append(newDir, 0);
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


