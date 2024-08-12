#include "SnakeInteractiveAnime.h"

SnakeInteractiveAnime::SnakeInteractiveAnime(int size)
    : BaseInteractiveAnime(size), game(size,size) {
      stepDuration = 1000;
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
