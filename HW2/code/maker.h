#ifndef MAKER_H
#define MAKER_H
#include <iostream>
#include <tuple>
#include "kitchen.h"
#include "player.h"
#include "tool.h"

class maker {
  private:
    std::vector<std::string> dishList;
    std::vector<std::string> needChopList;
  public:
    void clearDishList();
    void cleanHand(kitchen &, player &);
    void startMake(std::string &, kitchen &, player &);
    void chopItem(kitchen &, player &);
    void ovenItem(kitchen &, player &);
    void ovenPut(kitchen &, player &);
    void ovenTake(kitchen &, player &);
    void putItem(kitchen &, player &);
    void takeItem(std::string &, kitchen &, player &);
    bool checkDish(std::string &, kitchen &, player &, bool &);
};

#endif