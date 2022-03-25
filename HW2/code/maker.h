#ifndef MAKER_H
#define MAKER_H
#include <iostream>
#include <tuple>
#include "kitchen.h"
#include "customer.h"
#include "player.h"
#include "tool.h"

class maker {
  private:
    std::vector<std::string> dishList;
    std::vector<std::string> needChopList;
    std::vector<std::string> needOvenList;
    std::vector<std::string> needMergeList;
    bool useOvenFlag;
  public:
    maker(): useOvenFlag(false) {}
    void clearDishList();
    void cleanHand(kitchen &, player &);
    bool checkDish(customer &, kitchen &, player &, player &, bool &);
    void startMake(std::string &, customer &, kitchen &, player &);
    bool takeItem(std::string &, kitchen &, player &);
    void chopItem(kitchen &, player &);
    void ovenItem(customer &, kitchen &, player &);
    void ovenTake(kitchen &, player &);
    void putItem(kitchen &, player &);
    void mergeItem(kitchen &, player &);
    void moveItem(kitchen &, player &, std::string);
};

#endif