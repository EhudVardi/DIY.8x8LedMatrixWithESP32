#include "HWButtonHandler.h"

HWButtonHandler::HWButtonHandler(const std::vector<int>& pins, const std::vector<std::function<void()>>& handlers_onPress, const std::vector<std::function<void()>>& handlers_onRelease) {
    for (size_t i = 0; i < pins.size(); ++i) {
        buttons.emplace_back(pins[i]);
        buttons.back().onPress = handlers_onPress[i];
        buttons.back().onRelease = handlers_onRelease[i];
    }
}

void HWButtonHandler::updateButtons() {
    for (auto& button : buttons) {
        button.updateState();
    }
}

std::vector<HWButton>& HWButtonHandler::getButtons() {
    return buttons;
}
