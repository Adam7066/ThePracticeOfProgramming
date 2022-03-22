#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <utility>
#include <string>
#include <cmath>

class player {
  private:
    std::pair<int, int> posXY;
    std::string item;
  public:
    void setPos(int, int);
    void setItem(std::string &);
    std::pair<int, int> getPos() const;
    std::string getItem() const;
    bool move(std::pair<int, int>);
    void use(std::pair<int, int>);
    double getDistance(std::pair<int, int>);
};

#endif