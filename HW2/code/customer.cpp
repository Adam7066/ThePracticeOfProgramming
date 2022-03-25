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

std::string customer::chooseDish(kitchen &cookhouse) {
    for(auto &it : itemAward) {
        std::vector<std::string> itemList = tool::splitStr(it.first, "-");
        bool flag = true;
        for(auto &i : itemList) {
            if(i == "CHOPPED_STRAWBERRIES" || i == "CROISSANT" || i == "TART") {
                if(cookhouse.getTableItemPos(i) == std::make_pair(-1, -1)) {
                    flag = false;
                    break;
                }
            }
        }
        if(flag) return it.first;
    }
    std::string retStr;
    double retW = 0.0;
    for(auto &it : itemAward) {
        std::vector<std::string> itemList = tool::splitStr(it.first, "-");
        int tmpW = 0;
        for(auto &i : itemList) {
            if(i == "CHOPPED_STRAWBERRIES") tmpW += 2;
            else if(i == "CROISSANT") tmpW += 3;
            else if(i == "TART") tmpW += 5;
            else tmpW += 1;
        }
        if(it.second * 1.0 / tmpW > retW)
            retStr = it.first;
    }
    return retStr;
}