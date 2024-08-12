#include "SnakeInteractiveAnime.h"

SnakeInteractiveAnime::SnakeInteractiveAnime(int size)
    : BaseInteractiveAnime(size), game(size,size) {
      stepDuration = 1000;
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
			if (gameBoard.IsBodyCell(i,j))
				setPixel(i, j, true);
		}
	}
}

void SpiralAnime::SetInputHandlers() {
  inputHandlers[0] = [this]() {
    stepDuration = 50;
  };
  inputHandlers[1] = [this]() {
    stepDuration = 100;
  };
  inputHandlers[2] = [this]() {
    stepDuration = 250;
  };
  inputHandlers[3] = [this]() {
    stepDuration = 500;
  };
}
