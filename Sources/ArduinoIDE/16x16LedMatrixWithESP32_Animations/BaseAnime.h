#ifndef BASE_ANIME_H
#define BASE_ANIME_H

#include <Arduino.h>
#include <stdint.h>

class BaseAnime {
protected:
    int N;
    uint8_t* matrix;
    int stepDuration;

public:
    BaseAnime(int size);
    virtual ~BaseAnime();
    virtual void init() = 0;
    virtual void step() = 0;
    void clearMatrix();
    uint8_t* getMatrix();
    void setPixel(int x, int y, bool state);
    bool getPixel(int x, int y);
    int getStepDuration();
};

#endif
