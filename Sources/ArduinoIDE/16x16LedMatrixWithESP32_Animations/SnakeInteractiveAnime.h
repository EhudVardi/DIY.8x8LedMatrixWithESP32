#ifndef SNAKE_INTERACTIVE_ANIME_H
#define SNAKE_INTERACTIVE_ANIME_H

#include "BaseInteractiveAnime.h"
#include "SnakeGame.h"

class SnakeInteractiveAnime : public BaseInteractiveAnime {
private:
	SnakeGame game;
    
public:
    SnakeInteractiveAnime(int size);
    void init() override;
    void step() override;
    void SetInputHandlers() override;
};

#endif
