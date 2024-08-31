#ifndef TETRIS_INTERACTIVE_ANIME_H
#define TETRIS_INTERACTIVE_ANIME_H

#include "BaseInteractiveAnime.h"
#include "TetrisGame.h"

class TetrisInteractiveAnime : public BaseInteractiveAnime {
private:
  TetrisGame game;
  const float durationDiv = 10;
  const float durationCoef = (1 - durationDiv) / (durationDiv);

public:
  TetrisInteractiveAnime(int size);
  void init() override;
  void step() override;
  void SetInputHandlers() override;
  int getStepDuration() override;
};

#endif
