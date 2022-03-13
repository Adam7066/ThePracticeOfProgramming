#pragma once
#include <vector>
#include <string>

class maze {
  private:
    const unsigned int row, col;
    const std::vector<std::string> mp;
  public:
    maze(const unsigned int, const unsigned int, const std::vector<std::string>);
    bool canWalk(const int, const int) const;
};
