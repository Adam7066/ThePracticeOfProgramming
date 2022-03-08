#pragma once
#include <vector>
#include <string>

class maze {
  private:
    const unsigned int row, col;
    const std::vector<std::string> mp;
  public:
    maze(const unsigned int row, const unsigned int col, const std::vector<std::string> mp):
        row(row), col(col), mp(mp) {};
    bool isCanWalk(const int, const int);
};
