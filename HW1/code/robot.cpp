#include <iostream>
#include "robot.h"

robot::robot(const unsigned int ix, const unsigned int iy, const unsigned int idir) {
    x = ix;
    y = iy;
    direction = idir;
    step = 0;
    history.clear();
}

void robot::getBotPos(unsigned int &rx, unsigned int &ry) {
    rx = x;
    ry = y;
}

void robot::getNextPos(unsigned int &nx, unsigned int &ny) {
    nx = x + d[direction][0];
    ny = y + d[direction][1];
}

void robot::turn(const unsigned int td) {
    direction = (direction + td) % 4;
}

void robot::goNext() {
    history.push_back(std::make_tuple(x, y, direction));
    x = x + d[direction][0];
    y = y + d[direction][1];
    ++step;
}

unsigned long long robot::getRepeatPos() {
    for(size_t i = 0; i < history.size(); ++i) {
        if(std::get<0>(history[i]) == x && std::get<1>(history[i]) == y && std::get<2>(history[i]) == direction) {
            return i + 1;
        }
    }
    return 0;
}
