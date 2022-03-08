#include "maze.h"

bool maze::isCanWalk(const int x, const int y) {
    if(x<0 || x>=row || y<0 || y>=col || mp[x][y] == '#') return false;
    return true;
}