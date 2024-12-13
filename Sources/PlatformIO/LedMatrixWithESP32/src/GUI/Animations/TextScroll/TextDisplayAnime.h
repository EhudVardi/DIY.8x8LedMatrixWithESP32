#ifndef TEXT_DISPLAY_ANIME_H
#define TEXT_DISPLAY_ANIME_H

#include "../BaseInteractiveAnime.h"
#include <unordered_map>
#include <string>
#include <array>

class TextDisplayAnime : public BaseInteractiveAnime {
private:
    std::unordered_map<char, std::array<byte, 4>> characterMap;
    std::string text;
    int scrollOffset;
    int textIndex;
    bool isScrolling;

public:
    TextDisplayAnime(int size);
    TextDisplayAnime(int size, const std::string& initialText);
    void setText(const std::string& text);
    void init(LedMatrixHandler* ledMatrixHandler) override;
    void step(LedMatrixHandler* ledMatrixHandler) override;
    void SetInputHandlers() override;

private:
    void initializeCharacterMap();
    void addCharacterToMatrix(LedMatrixHandler* ledMatrixHandler, const std::array<byte, 4>& charMatrix, int xOffset);
};

#endif
