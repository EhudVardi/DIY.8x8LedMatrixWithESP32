#include "BaseInteractiveAnime.h"

BaseInteractiveAnime::BaseInteractiveAnime(int size, int buttonCount)
    : BaseAnime(size), inputs(buttonCount), buttons(buttonCount) {}  // Initialize buttons with the specified count

void BaseInteractiveAnime::setButtonState(int buttonIdx, ButtonState newState) {
    if (buttonIdx >= 0 && buttonIdx < inputs) {  // Check if index is within bounds
        buttons[buttonIdx].state = newState;
    }
}
ButtonState BaseInteractiveAnime::getButtonState(int buttonIdx) {
    if (buttonIdx >= 0 && buttonIdx < inputs) {  // Check if index is within bounds
        return buttons[buttonIdx].state;
    }
}

