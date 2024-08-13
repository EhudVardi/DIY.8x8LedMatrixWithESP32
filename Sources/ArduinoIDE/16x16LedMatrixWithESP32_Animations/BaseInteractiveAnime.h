#ifndef BASE_INTERACTIVE_ANIME_H
#define BASE_INTERACTIVE_ANIME_H

#include "BaseAnime.h"
#include <unordered_map>

typedef std::function<void()> InputHandler;

class BaseInteractiveAnime : public BaseAnime {
protected:
  std::unordered_map<int, InputHandler> inputHandlers;
  virtual void SetInputHandlers() = 0;
public:
  BaseInteractiveAnime(int matrixSize);
  virtual void SetInput(int inputNum);
};

#endif
