#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <vector>
#include <string>
#include <algorithm>

class customer {
  private:
    int num;
    std::vector<std::pair<std::string, int>> itemAward;
  public:
    void setNum(int);
    void addItemAward(std::string &, int);
    std::vector<std::pair<std::string, int>> getItemAward() const;
    void clearItemAward();
    std::string chooseDish();
};

#endif