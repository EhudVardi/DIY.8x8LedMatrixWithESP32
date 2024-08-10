#ifndef DIRECTION_H
#define DIRECTION_H

#define CWISE true
#define CCWISE false
enum Direction { L, D, R, U };
Direction Turn(Direction dir, bool clockWise);
//std::string directionToString(Direction dir);

#endif
