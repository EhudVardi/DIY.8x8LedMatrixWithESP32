#ifndef SNAKE_INTERACTIVE_ANIME_H
#define SNAKE_INTERACTIVE_ANIME_H

#include "BaseInteractiveAnime.h"

class SnakeInteractiveAnime : public BaseInteractiveAnime {
private:

public:
    SnakeInteractiveAnime(int size);
    void init() override;
    void step() override;
	  void setInput(int inputIdx) override;
};

#endif
