#include "maze.h"

maze::maze(const unsigned int row, const unsigned int col, const std::vector<std::string> mp):
    row(row), col(col), mp(mp) {}

bool maze::canWalk(const int x, const int y) const {
    if(x < 0 || x >= row || y < 0 || y >= col || mp[x][y] == obstacleChar)
        return false;
    return true;
}