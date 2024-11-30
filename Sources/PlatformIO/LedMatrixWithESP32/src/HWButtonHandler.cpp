#include "HWButtonHandler.h"

// HWButtonHandler constructor
HWButtonHandler::HWButtonHandler(const std::vector<int>& pins, const std::vector<std::function<void()>>& handlers_onPress, const std::vector<std::function<void()>>& handlers_onRelease) {
  for (size_t i = 0; i < pins.size(); ++i) {
    buttons.emplace_back(pins[i]);
    buttons.back().onPress = handlers_onPress[i];      // Assign the corresponding onPress handler
    buttons.back().onRelease = handlers_onRelease[i];  // Assign the corresponding onRelease handler
  }
}

// Update the state of all buttons (polling)
void HWButtonHandler::updateButtons() {
  for (auto& button : buttons) {
    button.updateState();
  }
}

// Get the list of buttons (for external use)
std::vector<HWButton>& HWButtonHandler::getButtons() {
  return buttons;
}
