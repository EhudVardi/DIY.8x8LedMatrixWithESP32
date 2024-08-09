#include "Direction.h"

Direction Turn(Direction dir, bool clockWise) {
    return static_cast<Direction>(((int)dir+4+(clockWise ? -1 : 1))%4);
}
/*
std::string directionToString(Direction dir) {
    switch (dir) {
        case L: return "Left";
        case D: return "Down";
        case R: return "Right";
        case U: return "Up";
        default: return "Unknown";
    }
}*/