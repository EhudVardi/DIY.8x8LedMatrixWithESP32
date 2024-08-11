#include "HWButtonHandler.h"

HWButtonHandler* HWButtonHandler::instance = nullptr;

HWButtonHandler::HWButtonHandler(const std::vector<int>& pins) {
    for (int pin : pins) {
        buttons.emplace_back(pin);
        attachInterrupt(digitalPinToInterrupt(pin), HWButtonHandler::isr, CHANGE);
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
