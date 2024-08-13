#include "SnakeInteractiveAnime.h"

SnakeInteractiveAnime::SnakeInteractiveAnime(int size)
    : BaseInteractiveAnime(size), game(size,size) {
      stepDuration = 500;
      SetInputHandlers();
    }

void SnakeInteractiveAnime::init() {
	game.InitGame();
}

void SnakeInteractiveAnime::step() {
	// step the game
	game.StepGame();
	// update display matrix from game board
	clearMatrix();
	Matrix2D gameBoard = game.GetBoard();
	for (int i=0; i<gameBoard.GetWidth(); i++) {
		for (int j=0; j<gameBoard.GetHeight(); j++) {
			if (!gameBoard.IsClearCell(i,j))
				setPixel(i, j, true);
		}
	}
}

void SnakeInteractiveAnime::SetInputHandlers() {
  inputHandlers[0] = [this]() {
    game.TurnSnake(U);
  };
  inputHandlers[1] = [this]() {
    game.TurnSnake(D);
  };
  inputHandlers[2] = [this]() {
    game.TurnSnake(L);
  };
  inputHandlers[3] = [this]() {
    game.TurnSnake(R);
  };
}
