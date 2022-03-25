#ifndef KITCHEN_H
#define KITCHEN_H
#include <vector>
#include <string>
#include <tuple>
#include "tool.h"

class kitchen {
  private:
    std::vector<std::string> maze;
    int tableNum;
    std::vector<std::tuple<int, int, std::string>> tableInfo;
    std::pair<std::string, int> ovenInfo;
    std::pair<int, int> dishwasherPosXY, windowPosXY, blueberriesPosXY, iceCreamPosXY,
        strawberriesPosXY, choppingboardPosXY, doughPosXY, ovenPosXY;
  public:
    void addMaze(std::string &);
    void setTableNum(int);
    void addTableInfo(int, int, std::string &);
    std::vector<std::tuple<int, int, std::string>> getTableInfo() const;
    void clearTableInfo();
    void setOvenInfo(std::string &, int);
    std::pair<std::string, int> getOvenInfo() const;
    std::pair<int, int> getTableItemPos(std::string) const;
    std::pair<int, int> getNearEmptyTablePos(std::string);
    std::pair<int, int> getPos(const std::string &) const;
    bool isEmptyTable(std::pair<int, int>);
};

#endif