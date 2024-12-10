#include "BaseInteractiveAnime.h"

BaseInteractiveAnime::BaseInteractiveAnime(int size)
    : BaseAnime(size) {
}

void BaseInteractiveAnime::SetInput(int inputNum) {
    if (inputHandlers.find(inputNum) != inputHandlers.end()) {
        inputHandlers[inputNum](true);  // Call the handler with true (set)
    }
}

void BaseInteractiveAnime::ResetInput(int inputNum) {
    if (inputHandlers.find(inputNum) != inputHandlers.end()) {
        inputHandlers[inputNum](false);  // Call the handler with false (reset)
    }
}

void BaseInteractiveAnime::RegisterInputHandler(int inputNum, InputHandler handler) {
    inputHandlers[inputNum] = handler;
}