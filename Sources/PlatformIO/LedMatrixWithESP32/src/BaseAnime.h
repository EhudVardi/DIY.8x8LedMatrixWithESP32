#ifndef BASE_ANIME_H
#define BASE_ANIME_H

#include <Arduino.h>
#include <stdint.h>
#include "LedMatrixHandler.h"

class BaseAnime {
protected:
    int stepDuration;

public:
    BaseAnime();
    virtual void init(LedMatrixHandler* ledMatrixHandler) = 0;
    virtual void step(LedMatrixHandler* ledMatrixHandler) = 0;
    virtual int getStepDuration();
};

#endif
