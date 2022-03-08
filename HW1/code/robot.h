#pragma once
#include <vector>
#include <tuple>

class robot {
  private:
    unsigned int x, y, direction;
    unsigned long long step;
    std::vector<std::tuple<unsigned int, unsigned int, unsigned int>> history;
  public:
    robot(const unsigned int, const unsigned int, const unsigned int);
    static constexpr int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    void getBotPos(unsigned int &, unsigned int &);
    void getNextPos(unsigned int &, unsigned int &);
    void turn(const unsigned int);
    void goNext();
    unsigned long long getRepeatPos();
};
