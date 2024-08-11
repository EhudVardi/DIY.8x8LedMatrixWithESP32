#ifndef BASE_INTERACTIVE_ANIME_H
#define BASE_INTERACTIVE_ANIME_H

#include "BaseAnime.h"
#include <vector>

enum class ButtonState {
    Released,
    Pressed
};

class Button {
public:
    ButtonState state;
    Button() : state(ButtonState::Released) {}
};

class BaseInteractiveAnime : public BaseAnime {
protected:
    int inputs;
    std::vector<Button> buttons; 

public:
    BaseInteractiveAnime(int matrixSize, int buttonCount);

    void setButtonState(int buttonIdx, ButtonState newState);
    ButtonState getButtonState(int buttonIdx);
};

#endif
