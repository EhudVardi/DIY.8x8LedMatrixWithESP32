#ifndef BASE_INTERACTIVE_ANIME_H
#define BASE_INTERACTIVE_ANIME_H

#include "BaseAnime.h"

class BaseInteractiveAnime : public BaseAnime {
protected:
	int inputs;
public:
  BaseInteractiveAnime(int matrixSize, int buttonCount);
	virtual void setInput(int inputIdx);
};

#endif
