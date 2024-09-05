#ifndef HW_BUTTON_HANDLER_H
#define HW_BUTTON_HANDLER_H

#include <Arduino.h>
#include <vector>
#include <functional>

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

  // Debounce parameters
  unsigned long lastDebounceTime;          // Last time the button state changed
  const unsigned long debounceDelay = 50;  // Debounce delay in milliseconds
  int lastReading;                         // Last stable reading from the button pin

  HWButton(int pin)
    : pin(pin), state(HWButtonState::Released), lastState(HWButtonState::Released), lastReading(HIGH), lastDebounceTime(0) {
    pinMode(pin, INPUT_PULLUP);
  }

  HWButtonState getState() {
    return state;
  }

  // Update the button state with debounce logic
  void updateState() {
    int currentReading = digitalRead(pin);

    // Check if the reading has changed (due to noise or press)
    if (currentReading != lastReading) {
      lastDebounceTime = millis();  // Reset the debounce timer
    }

    // Only update the button state if enough time has passed (debounce)
    if ((millis() - lastDebounceTime) > debounceDelay) {
      // State has been stable for the debounce delay, so update the button state
      HWButtonState currentState = (currentReading == LOW) ? HWButtonState::Pressed : HWButtonState::Released;

      if (currentState != state) {
        state = currentState;

        // Call the event handler if the button is pressed
        if (state == HWButtonState::Pressed && onPress) {
          onPress();
        }
      }
    }

    lastReading = currentReading;  // Update lastReading for the next iteration
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

public:
  HWButtonHandler(const std::vector<int>& pins, const std::vector<std::function<void()>>& handlers);
  void updateButtons();
  std::vector<HWButton>& getButtons();
};

#endif