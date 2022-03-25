#include "kitchen.h"

void kitchen::addMaze(std::string &kitchen_line) {
    maze.push_back(kitchen_line);
    int y = maze.size() - 1;
    for(size_t x = 0; x < kitchen_line.size(); ++x) {
        if(kitchen_line[x] == 'D') dishwasherPosXY = {x, y};
        else if(kitchen_line[x] == 'W') windowPosXY = {x, y};
        else if(kitchen_line[x] == 'B') blueberriesPosXY = {x, y};
        else if(kitchen_line[x] == 'I') iceCreamPosXY = {x, y};
        else if(kitchen_line[x] == 'S') strawberriesPosXY = {x, y};
        else if(kitchen_line[x] == 'C') choppingboardPosXY = {x, y};
        else if(kitchen_line[x] == 'H') doughPosXY = {x, y};
        else if(kitchen_line[x] == 'O') ovenPosXY = {x, y};
    }
}

void kitchen::setTableNum(int num) {
    tableNum = num;
}

void kitchen::addTableInfo(int x, int y, std::string &item) {
    tableInfo.emplace_back(x, y, item);
}

std::vector<std::tuple<int, int, std::string>> kitchen::getTableInfo() const {
    return tableInfo;
};

void kitchen::clearTableInfo() {
    tableInfo.clear();
}

void kitchen::setOvenInfo(std::string &contents, int timer) {
    ovenInfo = {contents, timer};
}

std::pair<std::string, int> kitchen::getOvenInfo() const {
    return ovenInfo;
}

std::pair<int, int> kitchen::getTableItemPos(std::string item) const {
    for(int i = 0; i < tableNum; ++i) {
        if(std::get<2>(tableInfo[i]) == item)
            return {std::get<0>(tableInfo[i]), std::get<1>(tableInfo[i])};
    }
    return {-1, -1};
}

std::pair<int, int> kitchen::getNearEmptyTablePos(std::string item) {
    std::pair<int, int> wantNearPos = getPos(item);
    for(int i = 0; i < 8; ++i) {
        std::pair<int, int> nPos = {wantNearPos.first + tool::d[i][0], wantNearPos.second + tool::d[i][1]};
        if(isEmptyTable(nPos)) return nPos;
    }
    return {-1, -1};
}

std::pair<int, int> kitchen::getPos(const std::string &item) const {
    if(item == "WINDOW") return windowPosXY;
    else if(item == "DISH") return dishwasherPosXY;
    else if(item == "BLUEBERRIES") return blueberriesPosXY;
    else if(item == "ICE_CREAM") return iceCreamPosXY;
    else if(item == "STRAWBERRIES") return strawberriesPosXY;
    else if(item == "CHOPPED") return choppingboardPosXY;
    else if(item == "DOUGH") return doughPosXY;
    else if(item == "OVEN") return ovenPosXY;
    return {-1, -1};
}

bool kitchen::isEmptyTable(std::pair<int, int> posXY) {
    if(posXY.first < 0 || posXY.first > 10) return false;
    if(posXY.second < 0 || posXY.second > 6) return false;
    if(maze[posXY.second][posXY.first] != '#') return false;
    for(auto &it : tableInfo) {
        if(std::get<0>(it) == posXY.first && std::get<1>(it) == posXY.second)
            return false;
    }
    return true;
}