#include "HWButtonHandler.h"

HWButtonHandler* HWButtonHandler::instance = nullptr;

HWButtonHandler::HWButtonHandler(const std::vector<int>& pins, const std::vector<std::function<void()>>& handlers) {
  for (size_t i = 0; i < pins.size(); ++i) {
    buttons.emplace_back(pins[i]);
    buttons.back().onPress = handlers[i];  // Assign the corresponding handler
    attachInterrupt(digitalPinToInterrupt(pins[i]), HWButtonHandler::isr, CHANGE);
  }
  instance = this;
}

void HWButtonHandler::updateButtons() {
  for (auto& button : buttons) {
    button.updateState();
  }
}
std::vector<HWButton>& HWButtonHandler::getButtons() {
  return buttons;
}

void HWButtonHandler::isr() {
  if (instance != nullptr) {
    instance->updateButtons();
  }
}
