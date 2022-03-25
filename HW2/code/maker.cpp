#include "maker.h"

void maker::clearDishList() {
    dishList.clear();
    needChopList.clear();
    needOvenList.clear();
    needMergeList.clear();
    useOvenFlag = false;
}

void maker::cleanHand(kitchen &cookhouse, player &me) {
    putItem(cookhouse, me);
    return;
}

void maker::startMake(std::string &dish, customer &client, kitchen &cookhouse, player &me) {
    if(dishList.empty()) {
        dishList = tool::splitStr(dish, "-");
        for(size_t i = 0; i < dishList.size(); ++i) {
            bool flag = cookhouse.getTableItemPos(dishList[i]) == std::make_pair(-1, -1);
            if(dishList[i] == "CHOPPED_STRAWBERRIES" && flag)
                needChopList.push_back(tool::splitStr(dishList[i], "_")[1]);
            else if(dishList[i] == "CROISSANT" && flag)
                needOvenList.push_back("DOUGH");
            else if(dishList[i] == "TART" && flag) {
                needChopList.push_back("DOUGH");
                needOvenList.push_back("RAW_TART");
            }
        }
        dishList.push_back("WINDOW");
    }
    std::cerr << "dish: " << dish << std::endl;
    // std::cerr << "needChop: " << std::endl;
    // for(auto &it : needChopList)
    //     std::cerr << "\t" << it << std::endl;
    // std::cerr << "needMerge: " << std::endl;
    // for(auto &it : needMergeList)
    //     std::cerr << "\t" << it << std::endl;
    // std::cerr << "needOven: " << std::endl;
    // for(auto &it : needOvenList)
    //     std::cerr << "\t" << it << std::endl;

    if(cookhouse.getOvenInfo().first == "CROISSANT" || cookhouse.getOvenInfo().first == "TART") {
        if(useOvenFlag || (!useOvenFlag && cookhouse.getOvenInfo().second < 5)) {
            ovenTake(cookhouse, me);
            return;
        }
    }
    else if(useOvenFlag) {
        std::cout << "WAIT" << std::endl;
        return;
    }
    if(takeItem(dish, cookhouse, me)) return;
    if(!needChopList.empty()) chopItem(cookhouse, me);
    else if(!needMergeList.empty()) mergeItem(cookhouse, me);
    else if(!needOvenList.empty() && cookhouse.getOvenInfo().first == "NONE")
        ovenItem(client, cookhouse, me);
    else {
        std::cerr << "Nothing can do!! QAQ" << std::endl;
        int chopStraCnt = 0, chopDougCnt = 0;
        for(auto &it : cookhouse.getTableInfo()) {
            std::string item = std::get<2>(it);
            if(item == "CHOPPED_STRAWBERRIES") ++chopStraCnt;
            else if(item == "CHOPPED_DOUGH") ++chopDougCnt;
        }
        if(chopStraCnt < 1 || chopDougCnt < 1) {
            needChopList.push_back(
                (chopStraCnt <= chopDougCnt)
                ? "STRAWBERRIES"
                : "DOUGH"
            );
            std::cout << "WAIT" << std::endl;
        }
        else moveItem(cookhouse, me, "WINDOW");
    }
}

void maker::moveItem(kitchen &cookhouse, player &me, std::string item) {
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY;
    if(meItem != "NONE" && meItem != "CHOPPED_STRAWBERRIES") {
        putItem(cookhouse, me);
        return;
    }
    std::pair<int, int> nearItemPosXY = cookhouse.getNearEmptyTablePos(item);
    if(nearItemPosXY != std::make_pair(-1, -1)) {
        if(meItem == "NONE") {
            auto tableInfo = cookhouse.getTableInfo();
            for(auto &it : tableInfo) {
                if(std::get<2>(it) == "CHOPPED_STRAWBERRIES") {
                    dishPosXY = cookhouse.getTableItemPos(std::get<2>(it));
                    break;
                }
            }
            if(dishPosXY != std::make_pair(-1, -1)) {
                if(me.move(dishPosXY)) return;
                else {
                    me.use(dishPosXY);
                    return;
                }
            }
        }
        else {
            if(me.move(nearItemPosXY)) return;
            else {
                me.use(nearItemPosXY);
                return;
            }
        }
    }
    std::cout << "WAIT" << std::endl;
}

void maker::ovenTake(kitchen &cookhouse, player &me) {
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY = cookhouse.getPos("OVEN");
    if(meItem != "NONE") {
        putItem(cookhouse, me);
        return;
    }
    if(me.move(dishPosXY)) return;
    else {
        me.use(dishPosXY);
        useOvenFlag = false;
        return;
    }
}

void maker::mergeItem(kitchen &cookhouse, player &me) {
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY;
    std::string tmpItem;
    if(needMergeList[0] == "RAW_TART") {
        if(meItem == "RAW_TART") {
            needMergeList.erase(needMergeList.begin());
            putItem(cookhouse, me);
            return;
        }
        if(meItem != "NONE") {
            if(meItem != "CHOPPED_DOUGH" && meItem != "BLUEBERRIES") {
                putItem(cookhouse, me);
                return;
            }
            tmpItem = (meItem == "CHOPPED_DOUGH")
                      ? "BLUEBERRIES"
                      : "CHOPPED_DOUGH";
        }
        else tmpItem = "CHOPPED_DOUGH";
        dishPosXY = (tmpItem == "CHOPPED_DOUGH")
                    ? cookhouse.getTableItemPos(tmpItem)
                    : cookhouse.getPos(tmpItem);
        if(dishPosXY == std::make_pair(-1, -1)) {
            needChopList.push_back("DOUGH");
            std::cout << "WAIT" << std::endl;
            return;
        }
        if(me.move(dishPosXY)) return;
        else {
            me.use(dishPosXY);
            return;
        }
    }
}

void maker::ovenItem(customer &client, kitchen &cookhouse, player &me) {
    std::vector<std::pair<std::string, int>> vpsi;
    vpsi.push_back({"DOUGH", 0});
    vpsi.push_back({"RAW_TART", 0});
    for(auto &it : client.getItemAward()) {
        auto itemList = tool::splitStr(it.first, "-");
        for(auto &i : itemList) {
            if(i == "CROISSANT") ++vpsi[0].second;
            else if(i == "TART") ++vpsi[1].second;
        }
    }
    sort(vpsi.begin(), vpsi.end(), [](std::pair<std::string, int> &a, std::pair<std::string, int> &b) {
        if(a.second != b.second) return a.second > b.second;
        else return a.first > b.first;
    });
    if(vpsi[0].first == "DOUGH")
        sort(needOvenList.begin(), needOvenList.end());
    else
        sort(needOvenList.begin(), needOvenList.end(), std::greater<std::string>());
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY;
    std::string tmpItem;
    if(meItem != "NONE" && meItem != needOvenList[0]) {
        putItem(cookhouse, me);
        return;
    }
    tmpItem = (meItem == needOvenList[0])
              ? "OVEN"
              : needOvenList[0];
    dishPosXY = (tmpItem == "RAW_TART")
                ? cookhouse.getTableItemPos(tmpItem)
                : cookhouse.getPos(tmpItem);
    if(dishPosXY == std::make_pair(-1, -1)) {
        needMergeList.push_back(tmpItem);
        std::cout << "WAIT" << std::endl;
        return;
    }
    else {
        if(me.move(dishPosXY)) return;
        else {
            me.use(dishPosXY);
            if(tmpItem == "OVEN") {
                useOvenFlag = true;
                needOvenList.erase(needOvenList.begin());
            }
            return;
        }
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
    tmpItem = (meItem == needChopList[0])
              ? "CHOPPED"
              : needChopList[0];
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
    for(int i = 0; i < 8; ++i) {
        std::pair<int, int> nPos = {me.getPos().first + tool::d[i][0], me.getPos().second + tool::d[i][1]};
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

bool maker::takeItem(std::string &dish, kitchen &cookhouse, player &me) {
    if(!needChopList.empty() || !needOvenList.empty()) return false;
    std::string meItem = me.getItem();
    std::pair<int, int> dishPosXY;
    if(meItem == "NONE") {
        for(auto &it : cookhouse.getTableInfo()) {
            std::string item = std::get<2>(it);
            if(item.find("DISH") != std::string::npos) {
                auto itemList = tool::splitStr(item, "-");
                bool canUseFlag = true;
                for(auto &i : itemList) {
                    if(dish.find(i) == std::string::npos) {
                        canUseFlag = false;
                        break;
                    }
                }
                if(canUseFlag) {
                    dishPosXY = {std::get<0>(it), std::get<1>(it)};
                    if(me.move(dishPosXY)) return true;
                    else {
                        me.use(dishPosXY);
                        return true;
                    }
                }
            }
        }
    }
    if(meItem != "NONE" && meItem.find("DISH") == std::string::npos) {
        putItem(cookhouse, me);
        return true;
    }
    std::vector<std::string> tmpDishList = dishList;
    std::vector<std::string> meItemList = tool::splitStr(meItem, "-");
    for(auto &it : meItemList) {
        auto findPos = std::find(tmpDishList.begin(), tmpDishList.end(), it);
        if(findPos != tmpDishList.end())
            tmpDishList.erase(findPos);
    }
    if(!tmpDishList.empty()) {
        bool itemOnTableFlag = true;
        std::string tmpStr[] = {"DISH", "WINDOW", "ICE_CREAM", "BLUEBERRIES"};
        for(auto &it : tmpStr) {
            if(tmpDishList[0] == it) {
                itemOnTableFlag = false;
                break;
            }
        }
        dishPosXY = (itemOnTableFlag)
                    ? cookhouse.getTableItemPos(tmpDishList[0])
                    : cookhouse.getPos(tmpDishList[0]);
        if(dishPosXY != std::make_pair(-1, -1)) {
            if(me.move(dishPosXY)) return true;
            else {
                me.use(dishPosXY);
                if(tmpDishList[0] == "WINDOW") {
                    dish.clear();
                    clearDishList();
                }
                return true;
            }
        }
        else {
            auto tableInfo = cookhouse.getTableInfo();
            for(auto &it : tmpDishList) {
                bool findFlag = false;
                if(it != "DISH" && it != "WINDOW" && it != "ICE_CREAM" && it != "BLUEBERRIES") {
                    for(auto &i : tableInfo) {
                        if(it == std::get<2>(i)) {
                            findFlag = true;
                            break;
                        }
                    }
                    if(!findFlag) {
                        if(it == "CHOPPED_STRAWBERRIES")
                            needChopList.push_back(tool::splitStr(it, "_")[1]);
                        else if(it == "CROISSANT")
                            needOvenList.push_back("DOUGH");
                        else if(it == "TART") {
                            needChopList.push_back("DOUGH");
                            needOvenList.push_back("RAW_TART");
                        }
                        std::cout << "WAIT" << std::endl;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool maker::checkDish(customer &client, kitchen &cookhouse, player &me, player &partner, bool &checkDishFlag) {
    if(checkDishFlag) {
        if(me.move(cookhouse.getPos("DISH"))) return true;
        else {
            me.use(cookhouse.getPos("DISH"));
            checkDishFlag = false;
            return true;
        }
    }
    int cntUsedDish = 0;
    for(auto &it : cookhouse.getTableInfo()) {
        if(std::get<2>(it).find("DISH") != std::string::npos)
            ++cntUsedDish;
    }
    if(me.getItem().find("DISH") != std::string::npos)
        ++cntUsedDish;
    if(partner.getItem().find("DISH") != std::string::npos)
        ++cntUsedDish;
    if(cntUsedDish >= 3) {
        std::string meItem = me.getItem();
        if(meItem == "NONE") {
            for(auto &it : cookhouse.getTableInfo()) {
                std::string item = std::get<2>(it);
                if(item.find("DISH") != std::string::npos) {
                    std::vector<std::string> itemList = tool::splitStr(item, "-");
                    bool needFlag = false;
                    for(auto &i : client.getItemAward()) {
                        bool flag = true;
                        for(auto &j : itemList) {
                            if(i.first.find(j) == std::string::npos) {
                                flag = false;
                                break;
                            }
                        }
                        if(flag) {
                            needFlag = true;
                            break;
                        }
                    }
                    if(!needFlag) {
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
        else if(meItem.find("DISH") != std::string::npos) {
            auto meItemList = tool::splitStr(meItem, "-");
            bool needFlag = false;
            for(auto &i : client.getItemAward()) {
                bool flag = true;
                for(auto &j : meItemList) {
                    if(i.first.find(j) == std::string::npos) {
                        flag = false;
                        break;
                    }
                }
                if(flag) {
                    needFlag = true;
                    break;
                }
            }
            if(!needFlag) {
                checkDishFlag = true;
                std::cout << "WAIT" << std::endl;
                return true;
            }
        }
    }
    return false;
}