#pragma once
#include <utility>
#include <vector>
#include <tuple>

class robot {
  private:
    unsigned int x, y, direction;
    unsigned long long step;
    std::vector<std::tuple<const unsigned int, const unsigned int, const unsigned int>> history;
  public:
    robot(const std::pair<unsigned int, unsigned int>, const unsigned int);
    static constexpr int d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    std::pair<unsigned int, unsigned int> getBotPos() const;
    std::pair<int, int> getNextPos() const;
    void turn(const unsigned int);
    void goNext();
    unsigned long long getRepeatPos() const;
};
