#include "Direction.h"
#include <cmath>

Direction Turn(Direction dir, bool clockWise) {
    return static_cast<Direction>(((int)dir + 4 + (clockWise ? -1 : 1)) % 4);
}
bool IsDirectionsAdjacent(Direction d1, Direction d2) {
    int diff = abs(d1 - d2);
    return diff == 1 || diff == 3;
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