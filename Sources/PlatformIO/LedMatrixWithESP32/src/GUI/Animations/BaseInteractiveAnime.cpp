#include "BaseInteractiveAnime.h"

BaseInteractiveAnime::BaseInteractiveAnime() {}

void BaseInteractiveAnime::SetInput(int inputNum) {
    if (inputHandlers.find(inputNum) != inputHandlers.end()) {
        inputHandlers[inputNum](true);
    }
}

void BaseInteractiveAnime::ResetInput(int inputNum) {
    if (inputHandlers.find(inputNum) != inputHandlers.end()) {
        inputHandlers[inputNum](false);
    }
}

void BaseInteractiveAnime::RegisterInputHandler(int inputNum, InputHandler handler) {
    inputHandlers[inputNum] = handler;
}