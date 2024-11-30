#ifndef SNAKE_INTERACTIVE_ANIME_H
#define SNAKE_INTERACTIVE_ANIME_H

#include "BaseInteractiveAnime.h"
#include "SnakeGame.h"

class SnakeInteractiveAnime : public BaseInteractiveAnime {
private:
  SnakeGame game;
  const float durationDiv = 10;
  const float durationCoef = (1 - durationDiv) / (durationDiv);

public:
  SnakeInteractiveAnime(int size);
  void init() override;
  void step() override;
  void SetInputHandlers() override;
  int getStepDuration() override;
};

#endif
