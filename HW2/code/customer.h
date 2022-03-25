#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include "tool.h"
#include "kitchen.h"

class customer {
  private:
    int num;
    std::vector<std::pair<std::string, int>> itemAward;
  public:
    void setNum(int);
    void addItemAward(std::string &, int);
    std::vector<std::pair<std::string, int>> getItemAward() const;
    void clearItemAward();
    std::string chooseDish(kitchen &);
};

#endif