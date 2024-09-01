#ifndef TETRIS_INTERACTIVE_ANIME_H
#define TETRIS_INTERACTIVE_ANIME_H

#include "BaseInteractiveAnime.h"
#include "TetrisGame.h"

class TetrisInteractiveAnime : public BaseInteractiveAnime {
private:
  TetrisGame game;

  const float durationDiv = 50;
  int getGameStepDuration();
  unsigned long previousMillis = 0;

public:
  TetrisInteractiveAnime(int size);
  void init() override;
  void step() override;
  void SetInputHandlers() override;
};

#endif
