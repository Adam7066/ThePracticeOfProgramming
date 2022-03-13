#include <iostream>
#include "robot.h"

constexpr int robot::d[][2];

robot::robot(const std::pair<unsigned int, unsigned int>posXY, const unsigned int dir) :
    x(posXY.first), y(posXY.second), direction(dir), step(0) {}

std::pair<unsigned int, unsigned int> robot::getBotPos() const {
    return {x, y};
}

std::pair<int, int> robot::getNextPos() const {
    return {x + d[direction][0], y + d[direction][1]};
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

unsigned long long robot::getRepeatPos() const {
    for(size_t i = 0; i < history.size(); ++i) {
        if(std::get<0>(history[i]) == x && std::get<1>(history[i]) == y && std::get<2>(history[i]) == direction) {
            return i + 1;
        }
    }
    return 0;
}
