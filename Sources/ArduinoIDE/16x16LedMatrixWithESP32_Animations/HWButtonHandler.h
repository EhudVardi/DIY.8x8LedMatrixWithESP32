#ifndef HW_BUTTON_HANDLER_H
#define HW_BUTTON_HANDLER_H

#include <Arduino.h>
#include <vector>
#include <functional>  // Required for std::function

// Enum for button states
enum class HWButtonState {
  Released,
  Pressed
};

// HWButton class to represent individual buttons
class HWButton {
public:
  int pin;
  volatile HWButtonState state;
  volatile HWButtonState lastState;
  std::function<void()> onPress;  // Event handler

  HWButton(int pin)
    : pin(pin), state(HWButtonState::Released), lastState(HWButtonState::Released) {
    pinMode(pin, INPUT_PULLUP);
  }

  HWButtonState getState() {
    return state;
  }

  void updateState() {
    HWButtonState currentState = digitalRead(pin) == LOW ? HWButtonState::Pressed : HWButtonState::Released;
    if (currentState != state) {
      state = currentState;
      if (state == HWButtonState::Pressed && onPress) {
        onPress();  // Call the event handler when pressed
      }
    }
  }

  bool stateChanged() {
    if (state != lastState) {
      lastState = state;
      return true;
    }
    return false;
  }
};

// HWButtonHandler class to manage multiple buttons
class HWButtonHandler {
private:
  std::vector<HWButton> buttons;
  static HWButtonHandler* instance;
  static void isr();  // ISR function

public:
  HWButtonHandler(const std::vector<int>& pins, const std::vector<std::function<void()>>& handlers);
  void updateButtons();
  std::vector<HWButton>& getButtons();
};

#endif
