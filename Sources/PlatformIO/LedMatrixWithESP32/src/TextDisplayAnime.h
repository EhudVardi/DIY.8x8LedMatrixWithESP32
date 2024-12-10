#ifndef TEXT_DISPLAY_ANIME_H
#define TEXT_DISPLAY_ANIME_H

#include "BaseInteractiveAnime.h"
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
    void setText(const std::string& text);
    void init() override;
    void step() override;
    void SetInputHandlers() override;

private:
    void initializeCharacterMap();
    void addCharacterToMatrix(const std::array<byte, 4>& charMatrix, int xOffset);
};

#endif
