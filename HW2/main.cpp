#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <cmath>

// "WINDOW", "DISH", "ICE_CREAM", "BLUEBERRIES",
// "STRAWBERRIES", "CHOPPED", "Dough", "OVEN", "CROISSANT"

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

    std::pair<int, int> getPos(const std::string &) const;
    bool isEmptyTable(std::pair<int, int>);
};

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

class player {
  private:
    std::pair<int, int> posXY;
    std::string item;
  public:
    void setPos(int, int);
    void setItem(std::string &);
    std::pair<int, int> getPos() const;
    std::string getItem() const;
    bool move(std::pair<int, int>);
    void use(std::pair<int, int>);
    double getDistance(std::pair<int, int>);
};

class maker {
  private:
    std::vector<std::string> dishList;
    std::vector<std::string> needChopList;
  public:
    void clearDishList();
    void cleanHand(kitchen &, player &);
    void startMake(std::string &, kitchen &, player &, player &);
    void chopItem(kitchen &, player &);
    void ovenItem(kitchen &, player &);
    void ovenPut(kitchen &, player &);
    void ovenTake(kitchen &, player &);
    void putItem(kitchen &, player &);
    void takeItem(std::string &, kitchen &, player &);
    bool checkDish(std::string &, kitchen &, player &, bool &);
};

class tool {
  public:
    static std::vector<std::string> splitStr(std::string &, std::string);
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    customer client;
    kitchen cookhouse;
    player me, partner;
    std::string dish;
    maker cook;
    bool checkDishFlag = false;

    int num_all_customers;
    std::cin >> num_all_customers;
    client.setNum(num_all_customers);
    for (int i = 0; i < num_all_customers; ++i) {
        std::string customer_item;
        int customer_award;
        std::cin >> customer_item >> customer_award;
        client.addItemAward(customer_item, customer_award);
    }
    std::cin.ignore();
    for (int i = 0; i < 7; ++i) {
        std::string kitchen_line;
        getline(std::cin, kitchen_line);
        cookhouse.addMaze(kitchen_line);
    }

    while (1) {
        int turns_remaining;
        std::cin >> turns_remaining;
        if(turns_remaining <= 2) {
            dish.clear();
            cook.clearDishList();
        }
        int player_x, player_y;
        std::string player_item;
        std::cin >> player_x >> player_y >> player_item;
        me.setPos(player_x, player_y);
        me.setItem(player_item);
        int partner_x, partner_y;
        std::string partner_item;
        std::cin >> partner_x >> partner_y >> partner_item;
        partner.setPos(partner_x, partner_y);
        partner.setItem(partner_item);
        int num_tables_with_items;
        std::cin >> num_tables_with_items;
        cookhouse.setTableNum(num_tables_with_items);
        cookhouse.clearTableInfo();
        for (int i = 0; i < num_tables_with_items; i++) {
            int table_x, table_y;
            std::string item;
            std::cin >> table_x >> table_y >> item;
            cookhouse.addTableInfo(table_x, table_y, item);
        }
        std::string oven_contents;
        int oven_timer;
        std::cin >> oven_contents >> oven_timer;
        cookhouse.setOvenInfo(oven_contents, oven_timer);
        int num_customers;
        std::cin >> num_customers;
        client.setNum(num_customers);
        client.clearItemAward();
        bool dishFlag = false;
        for (int i = 0; i < num_customers; i++) {
            std::string customer_item;
            int customer_award;
            std::cin >> customer_item >> customer_award;
            client.addItemAward(customer_item, customer_award);
            if(customer_item == dish) dishFlag = true;
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        // MOVE x y // USE x y // WAIT
        if(!dish.empty() && !dishFlag) {
            if(me.getItem() == "NONE") {
                dish.clear();
                cook.clearDishList();
                std::cout << "WAIT" << std::endl;
            }
            else cook.cleanHand(cookhouse, me);
        }
        else {
            if(dish.empty()) dish = client.chooseDish();
            if(cook.checkDish(dish, cookhouse, me, checkDishFlag)) continue;
            cook.startMake(dish, cookhouse, me, partner);
        }
    }
}

#pragma region kitchen
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

std::pair<int, int> kitchen::getPos(const std::string &item) const {
    if(item == "WINDOW") return windowPosXY;
    else if(item == "DISH") return dishwasherPosXY;
    else if(item == "BLUEBERRIES") return blueberriesPosXY;
    else if(item == "ICE_CREAM") return iceCreamPosXY;
    else if(item == "STRAWBERRIES") return strawberriesPosXY;
    else if(item == "CHOPPED") return choppingboardPosXY;
    else if(item == "DOUGH") return doughPosXY;
    else if(item == "OVEN") return ovenPosXY;
}

bool kitchen::isEmptyTable(std::pair<int, int> posXY) {
    if(maze[posXY.second][posXY.first] != '#') return false;
    for(auto &it : tableInfo) {
        if(std::get<0>(it) == posXY.first && std::get<1>(it) == posXY.second)
            return false;
    }
    return true;
}
#pragma endregion kitchen

#pragma region customer
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
#pragma endregion customer

#pragma region player
void player::setPos(int x, int y) {
    posXY.first = x;
    posXY.second = y;
}

void player::setItem(std::string &item) {
    this->item = item;
}

std::pair<int, int> player::getPos() const {
    return posXY;
}

std::string player::getItem() const {
    return item;
}

bool player::move(std::pair<int, int> to) {
    if(abs(posXY.first - to.first) <= 1 && abs(posXY.second - to.second) <= 1)
        return false;
    std::cout << "MOVE " << to.first << " " << to.second << std::endl;
    return true;
}

void player::use(std::pair<int, int> item) {
    std::cout << "USE " << item.first << " " << item.second << std::endl;
}

double player::getDistance(std::pair<int, int> item) {
    int x = item.first - posXY.first, y = item.second - posXY.second;
    return std::sqrt(x * x + y * y);
}
#pragma endregion player

#pragma region maker
void maker::clearDishList() {
    dishList.clear();
    needChopList.clear();
}

void maker::cleanHand(kitchen &cookhouse, player &me) {
    putItem(cookhouse, me);
    return;
}

void maker::startMake(std::string &dish, kitchen &cookhouse, player &me, player &partner) {
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
#pragma endregion maker

#pragma region tool
std::vector<std::string> tool::splitStr(std::string &str, std::string del) {
    std::vector<std::string> res;
    int start = 0, end = str.find(del);
    while(end != -1) {
        res.push_back(str.substr(start, end - start));
        start = end + del.size();
        end = str.find(del, start);
    }
    res.push_back(str.substr(start, end - start));
    return res;
}
#pragma endregion tool