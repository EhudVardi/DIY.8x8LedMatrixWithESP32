#ifndef BASE_INTERACTIVE_ANIME_H
#define BASE_INTERACTIVE_ANIME_H

#include "BaseAnime.h"
#include <unordered_map>

typedef std::function<void(bool)> InputHandler;

class BaseInteractiveAnime : public BaseAnime {
protected:
    std::unordered_map<int, InputHandler> inputHandlers;
    virtual void SetInputHandlers() = 0;
public:
    BaseInteractiveAnime();
    virtual void SetInput(int inputNum); // Call with true (set)
    virtual void ResetInput(int inputNum);  // Call with false (reset)
    void RegisterInputHandler(int inputNum, InputHandler handler);
};

#endif
