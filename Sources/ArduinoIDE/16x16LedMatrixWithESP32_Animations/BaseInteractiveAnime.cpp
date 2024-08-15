#include "BaseInteractiveAnime.h"

BaseInteractiveAnime::BaseInteractiveAnime(int size)
  : BaseAnime(size) {}

void BaseInteractiveAnime::SetInput(int inputNum) {
  // check if a handler with a key corresponds to the inputNum, and call it if exists
  if (inputHandlers.find(inputNum) != inputHandlers.end()) {
    inputHandlers[inputNum]();
  }
  SetInputHandlers();
}
