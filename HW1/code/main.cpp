#include <iostream>
#include <vector>
#include <string>
#include "maze.h"
#include "robot.h"

enum Face {
    up, right, down, left
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    unsigned int row, col, rx, ry;
    unsigned long long step;
    std::cin >> col >> row >> step;
    std::vector<std::string> mp;
    for(size_t i = 0; i < row; ++i) {
        std::string s;
        std::cin >> s;
        for(size_t j = 0; j < col; ++j) {
            if(s[j] == 'O') {
                rx = i;
                ry = j;
                s[j] = '.';
                break;
            }
        }
        mp.push_back(s);
    }
    maze mz(row, col, mp);
    robot bot(rx, ry, Face::up);
    bool repeatFlag = false;
    for(size_t i = 0; i < step; ++i) {
        unsigned int nx, ny;
        bot.getNextPos(nx, ny);
        while(!mz.isCanWalk(nx, ny)) {
            bot.turn(Face::right);
            bot.getNextPos(nx, ny);
        }
        if(!repeatFlag && i > 0) {
            unsigned long long repeatStep = bot.getRepeatPos();
            if(repeatStep > 0) {
                --repeatStep;
                i = step - ((step - repeatStep) % (i - repeatStep)) - 1;
                repeatFlag = true;
                continue;
            }
        }
        bot.goNext();
    }
    bot.getBotPos(rx, ry);
    std::cout << ry << " " << rx << std::endl;
    return 0;
}
