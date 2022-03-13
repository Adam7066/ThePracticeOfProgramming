#include <iostream>
#include <utility>
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
    unsigned int row, col;
    unsigned long long step;
    std::pair<unsigned int, unsigned int> posXY;
    std::cin >> col >> row >> step;
    std::vector<std::string> mp;
    for(size_t i = 0; i < row; ++i) {
        std::string s;
        std::cin >> s;
        for(size_t j = 0; j < col; ++j) {
            if(s[j] == 'O') {
                posXY = {i, j};
                s[j] = '.';
                break;
            }
        }
        mp.push_back(s);
    }
    maze mz(row, col, mp);
    robot bot(posXY, Face::up);
    bool repeatFlag = false;
    for(size_t i = 0; i < step; ++i) {
        std::pair<int, int> nextXY = bot.getNextPos();
        while(!mz.canWalk(nextXY.first, nextXY.second)) {
            bot.turn(Face::right);
            nextXY = bot.getNextPos();
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
    posXY = bot.getBotPos();
    std::cout << posXY.second << " " << posXY.first << std::endl;
    return 0;
}
