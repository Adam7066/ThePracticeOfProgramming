#include "customer.h"

void customer::setNum(int num) {
    this->num = num;
}

void customer::addItemAward(std::string &item, int award) {
    itemAward.push_back({item, award});
}

std::vector<std::pair<std::string, int>> customer::getItemAward() const {
    return itemAward;
};

void customer::clearItemAward() {
    itemAward.clear();
}

std::string customer::chooseDish() {
    sort(itemAward.begin(), itemAward.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
        if(a.second != b.second) return a.second > b.second;
        else return a.first < b.first;
    });
    return itemAward[0].first;
}