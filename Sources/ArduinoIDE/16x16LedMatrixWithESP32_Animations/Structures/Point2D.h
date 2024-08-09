#ifndef POINT2D_H
#define POINT2D_H

class Point2D {
public:
    int x, y;

    Point2D(int x = 0, int y = 0) : x(x), y(y) {}

    void Move(Direction dir, int length);
	//void Print();
};

#endif
