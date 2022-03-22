#include "player.h"

void player::setPos(int x, int y) {
    posXY.first = x;
    posXY.second = y;
}

void player::setItem(std::string &item) {
    this->item = item;
}

std::pair<int, int> player::getPos() const {
    return posXY;
}

std::string player::getItem() const {
    return item;
}

bool player::move(std::pair<int, int> to) {
    if(abs(posXY.first - to.first) <= 1 && abs(posXY.second - to.second) <= 1)
        return false;
    std::cout << "MOVE " << to.first << " " << to.second << std::endl;
    return true;
}

void player::use(std::pair<int, int> item) {
    std::cout << "USE " << item.first << " " << item.second << std::endl;
}

double player::getDistance(std::pair<int, int> item) {
    int x = item.first - posXY.first, y = item.second - posXY.second;
    return std::sqrt(x * x + y * y);
}