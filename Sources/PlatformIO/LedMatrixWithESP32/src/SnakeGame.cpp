#include "SnakeGame.h"

SnakeGame::SnakeGame(int width, int height)
    : boardMatrix(width, height), gameState(SnakeGameState::Initialized), gameSpeedPercent(0.0) {
    randomSeed(analogRead(0));
}

void SnakeGame::InitGame() {
    // init position of the snake tail
    tailPos.x = boardMatrix.GetWidth() / 2;
    tailPos.y = boardMatrix.GetHeight() / 2;
    // init body of the snake - one section
    snakeBody.append(L, 2);
    // paint current snake on the board
    PaintSnakeOnBoard();
    gameState = SnakeGameState::Running;
}

void SnakeGame::StepGame() {
    if (gameState != SnakeGameState::Running)
        return;

    // find snake next head position
    ListNode* snakeHead = snakeBody.getTail();
    Point2D headNextPos = GetSnakeHeadPos();
    headNextPos.Move(snakeHead->dir, 1);

    // if collision with border then end the game and return
    if (boardMatrix.IsPointOutOfBounds(headNextPos)) {
        gameState = SnakeGameState::Ended;
        return;
    }
    // if collision with snake body (except current tail position - allow that) then end the game and return
    if (boardMatrix.IsBodyCell(headNextPos.x, headNextPos.y) && !headNextPos.IsEqual(tailPos)) {
        gameState = SnakeGameState::Ended;
        return;
    }

    // check if next position is food.
    bool isNextHeadPosFood = boardMatrix.IsFoodCell(headNextPos.x, headNextPos.y);
    // stretch the head section and update matrix
    snakeHead->length++;
    boardMatrix.SetBodyCell(headNextPos.x, headNextPos.y);
    if (!isNextHeadPosFood) {  // if next head position was not food then also trim the tail
        // trim the tail section and update tail position and update the matrix
        boardMatrix.ClearCell(tailPos.x, tailPos.y);
        ListNode* snakeTail = snakeBody.getHead();
        snakeTail->length--;
        tailPos.Move(snakeTail->dir, 1);
        // trim entire tail section if its zero length
        if (snakeTail->length == 0)
            snakeBody.trimHead();
    }
    else {  // if it was food then speed up the game slightly
        gameSpeedPercent += 0.01;
    }

    // randomly add food
    if (RandomGenerator::nextFloat() > 0.9) {
        Point2D newFoodPos(0, 0);
        do {
            newFoodPos.x = RandomGenerator::nextInt(0, boardMatrix.GetWidth() - 1);
            newFoodPos.y = RandomGenerator::nextInt(0, boardMatrix.GetHeight() - 1);
        } while (!boardMatrix.IsClearCell(newFoodPos.x, newFoodPos.y));
        boardMatrix.SetFoodCell(newFoodPos.x, newFoodPos.y);
    }
}

void SnakeGame::TurnSnake(Direction newDir) {
    // allow to turn if new direction is adjecent to current snake head section direction (i.e., deny if its the same or opposite direction, else allow)
    // allow to turn only if the snake head section length is not zero (this signals that previous input has turned the snake but step did not occured yet)
    // to turn, simply append a new section to the snake head with a length of zero and with the new direction
    ListNode* snakeHead = snakeBody.getTail();
    if (snakeHead->length > 0 && IsDirectionsAdjacent(snakeHead->dir, newDir)) {
        snakeBody.append(newDir, 0);
    }
}

SnakeMatrix2D SnakeGame::GetBoard() const {
    return boardMatrix;
}

float SnakeGame::GetGameSpeedPercent() const {
    return gameSpeedPercent;
}

void SnakeGame::PaintSnakeOnBoard() {
    // clear the matrix
    boardMatrix.Clear();
    // paint the snake body
    Point2D travelPos(tailPos.x, tailPos.y);
    boardMatrix.SetBodyCell(travelPos.x, travelPos.y);  // paint first tail
    ListNode* travelNode = snakeBody.getHead();
    while (travelNode) {
        for (int i = 0; i < travelNode->length; i++) {
            travelPos.Move(travelNode->dir, 1);
            boardMatrix.SetBodyCell(travelPos.x, travelPos.y);
        }
        travelNode = travelNode->next;
    }
}

Point2D SnakeGame::GetSnakeHeadPos() {
    Point2D snakeHeadPos(tailPos.x, tailPos.y);
    ListNode* travelNode = snakeBody.getHead();
    while (travelNode) {
        snakeHeadPos.Move(travelNode->dir, travelNode->length);
        travelNode = travelNode->next;
    }
    return snakeHeadPos;
}
