#include "Point2D.h"

void Point2D::Move(Direction dir, int length) {
    switch (dir) {
        case L: x -= length; break;
        case D: y -= length; break;
        case R: x += length; break;
        case U: y += length; break;
    }
}
//void Point2D::Print() const {
//    std::cout << "(" << x << "," << y << ")" << std::endl;
//}