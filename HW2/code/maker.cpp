#include "maker.h"

void maker::clearDishList() {
    dishList.clear();
    needChopList.clear();
}

void maker::cleanHand(kitchen &cookhouse, player &me) {
    putItem(cookhouse, me);
    return;
}

void maker::startMake(std::string &dish, kitchen &cookhouse, player &me) {
    if(dishList.empty()) {
        dishList = tool::splitStr(dish, "-");
        for(size_t i = 0; i < dishList.size(); ++i) {
            if(dishList[i].find("CHOPPED") != std::string::npos) {
                int start = dishList[i].find("_") + 1;
                std::string tmpItem = dishList[i].substr(start, dishList[i].size() - start);
                needChopList.push_back(tmpItem);
            }
        }
        dishList.push_back("WINDOW");
    }
    std::string meItem = me.getItem();
    if((meItem.find("CHOPPED") != std::string::npos || meItem.find("CROISSANT") != std::string::npos)
            && meItem.find("DISH") == std::string::npos)
        putItem(cookhouse, me);
    else if(meItem.find("DOUGH") != std::string::npos && cookhouse.getOvenInfo().first != "NONE")
        putItem(cookhouse, me);
    else if(!needChopList.empty())
        chopItem(cookhouse, me);
    else if(cookhouse.getTableItemPos("CROISSANT") == std::make_pair(-1, -1) && cookhouse.getOvenInfo().first != "DOUGH") {
        if(cookhouse.getOvenInfo().first == "NONE")
            ovenPut(cookhouse, me);
        else if(cookhouse.getOvenInfo().first == "CROISSANT")
            ovenTake(cookhouse, me);
    }
    else takeItem(dish, cookhouse, me);
}

void maker::ovenPut(kitchen &cookhouse, player &me) {
    std::string meItem = me.getItem();
    if(meItem != "NONE" && meItem != "DOUGH") {
        putItem(cookhouse, me);
        return;
    }
    std::pair<int, int> dishPosXY = cookhouse.getPos((meItem == "DOUGH") ? "OVEN" : "DOUGH");
    if(me.move(dishPosXY)) return;
    else {
        me.use(dishPosXY);
        return;
    }
}

void maker::ovenTake(kitchen &cookhouse, player &me) {
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY = cookhouse.getPos("OVEN");
    if(meItem != "NONE" && meItem != "DOUGH") {
        putItem(cookhouse, me);
        return;
    }
    if(me.move(dishPosXY)) return;
    else {
        me.use(dishPosXY);
        return;
    }
}

void maker::chopItem(kitchen &cookhouse, player &me) {
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY;
    std::string tmpItem;
    if(meItem != "NONE" && meItem != needChopList[0]) {
        putItem(cookhouse, me);
        return;
    }
    if(meItem.find(needChopList[0]) == std::string::npos)
        tmpItem = needChopList[0];
    else tmpItem = "CHOPPED";
    dishPosXY = cookhouse.getPos(tmpItem);
    if(me.move(dishPosXY)) return;
    else {
        me.use(dishPosXY);
        if(tmpItem == "CHOPPED")
            needChopList.erase(needChopList.begin());
        return;
    }
}

void maker::putItem(kitchen &cookhouse, player &me) {
    int d[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for(int i = 0; i < 8; ++i) {
        std::pair<int, int> nPos = {me.getPos().first + d[i][0], me.getPos().second + d[i][1]};
        if(cookhouse.isEmptyTable(nPos)) {
            me.use(nPos);
            return;
        }
    }
    int nx = me.getPos().first, ny = me.getPos().second;
    nx += (nx >= 5) ? -2 : +2;
    ny += (ny >= 5) ? -2 : +2;
    if(me.move({nx, ny})) return;
}

void maker::takeItem(std::string &dish, kitchen &cookhouse, player &me) {
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY;
    if(meItem == "STRAWBERRIES" || meItem == "DOUGH") {
        putItem(cookhouse, me);
        return;
    }
    for(auto &it : dishList) {
        if(meItem.find(it) == std::string::npos) {
            if(it.find("CHOPPED") != std::string::npos) {
                dishPosXY = cookhouse.getTableItemPos(it);
                if(dishPosXY == std::make_pair(-1, -1)) {
                    int start = it.find("_") + 1;
                    std::string tmpItem = it.substr(start, it.size() - start);
                    needChopList.push_back(tmpItem);
                    std::cout << "WAIT" << std::endl;
                    return;
                }
            }
            else if(it == "CROISSANT") {
                dishPosXY = cookhouse.getTableItemPos(it);
                if(dishPosXY == std::make_pair(-1, -1)) {
                    std::cout << "WAIT" << std::endl;
                    return;
                }
            }
            else if(it == "DISH") {
                dishPosXY = cookhouse.getPos(it);
                for(auto &x : cookhouse.getTableInfo()) {
                    if(std::get<2>(x).find("DISH") != std::string::npos) {
                        dishPosXY = {std::get<0>(x), std::get<1>(x)};
                        break;
                    }
                }
            }
            else dishPosXY = cookhouse.getPos(it);
            if(me.move(dishPosXY)) return;
            else {
                me.use(dishPosXY);
                if(it == "WINDOW") {
                    dish.clear();
                    clearDishList();
                }
                return;
            }
        }
    }
}

bool maker::checkDish(std::string &dish, kitchen &cookhouse, player &me, bool &checkDishFlag) {
    if(checkDishFlag) {
        if(me.move(cookhouse.getPos("DISH"))) return true;
        else {
            me.use(cookhouse.getPos("DISH"));
            checkDishFlag = false;
            return true;
        }
    }
    std::string meItem = me.getItem();
    if(meItem == "NONE") {
        for(auto &it : cookhouse.getTableInfo()) {
            std::string item = std::get<2>(it);
            if(item.find("DISH") != std::string::npos) {
                std::vector<std::string> itemList = tool::splitStr(item, "-");
                bool flag = false;
                for(auto &i : itemList) {
                    if(dish.find(i) == std::string::npos) {
                        flag = true;
                        break;
                    }
                }
                if(flag) {
                    if(me.move({std::get<0>(it), std::get<1>(it)}))
                        return true;
                    else {
                        me.use({std::get<0>(it), std::get<1>(it)});
                        checkDishFlag = true;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}