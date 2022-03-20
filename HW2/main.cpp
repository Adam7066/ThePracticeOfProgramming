#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <cmath>
#include <unordered_map>

#pragma region kitchen
class kitchen {
  private:
    std::vector<std::string> maze;
    int tableNum;
    std::vector<std::tuple<int, int, std::string>> tableInfo;
    std::pair<int, int> dishwasherPosXY, windowPosXY, blueberriesPosXY, iceCreamPosXY;
  public:
    void addMaze(std::string &);
    void setTableNum(int);
    void setTableInfo(int, int, std::string &);
    std::pair<int, int> getPos(const std::string &) const;
};

void kitchen::addMaze(std::string &kitchen_line) {
    maze.push_back(kitchen_line);
    int y = maze.size() - 1;
    for(size_t x = 0; x < kitchen_line.size(); ++x) {
        if(kitchen_line[x] == 'D') dishwasherPosXY = std::make_pair(x, y);
        else if(kitchen_line[x] == 'W') windowPosXY = std::make_pair(x, y);
        else if(kitchen_line[x] == 'B') blueberriesPosXY = std::make_pair(x, y);
        else if(kitchen_line[x] == 'I') iceCreamPosXY = std::make_pair(x, y);
    }
}

void kitchen::setTableNum(int num) {
    tableNum = num;
}

void kitchen::setTableInfo(int x, int y, std::string &item) {
    tableInfo.emplace_back(x, y, item);
}

std::pair<int, int> kitchen::getPos(const std::string &item) const {
    if(item == "WINDOW") return windowPosXY;
    else if(item == "DISH") return dishwasherPosXY;
    else if(item == "BLUEBERRIES") return blueberriesPosXY;
    else if(item == "ICE_CREAM") return iceCreamPosXY;
    return std::make_pair(-1, -1);
}
#pragma endregion kitchen

#pragma region customer
class customer {
  private:
    int num;
    std::vector<std::pair<std::string, int>> itemAward;
  public:
    void setNum(int);
    void addItemAward(std::string &, int);
    void clearItemAward();
    std::string chooseDish();
};

void customer::setNum(int num) {
    this->num = num;
}

void customer::addItemAward(std::string &item, int award) {
    itemAward.push_back({item, award});
}

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
class player {
  private:
    std::pair<int, int> posXY;
    std::string item;
  public:
    void setPos(int, int);
    void setItem(std::string &);
    std::pair<int, int> getPos() const;
    std::string getItem() const;
};

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
#pragma endregion player

#pragma region maker
class maker {
  private:
    static const std::string itemType[];
    std::vector<std::string> dishList;
    std::vector<std::string> splitStr(std::string &, std::string);
  public:
    void clearDishList();
    bool startMake(std::string &, kitchen &, player &);
};
const std::string maker::itemType[] = {"WINDOW", "DISH", "ICE_CREAM", "BLUEBERRIES"};

std::vector<std::string> maker::splitStr(std::string &str, std::string del) {
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

void maker::clearDishList() {
    dishList.clear();
}

bool maker::startMake(std::string &dish, kitchen &cookhouse, player &me) {
    if(dishList.empty()) {
        dishList = splitStr(dish, "-");
        dishList.push_back(itemType[0]); // add WINDOW
    }
    std::string nextItem, meItem = me.getItem();
    for(auto &it : dishList) {
        if(meItem.find(it) == std::string::npos) {
            nextItem = it;
            break;
        }
    }
    std::pair<int, int> mePosXY = me.getPos();
    std::pair<int, int> dishPosXY = cookhouse.getPos(nextItem);
    if(abs(mePosXY.first - dishPosXY.first) > 1 || abs(mePosXY.second - dishPosXY.second) > 1) {
        std::cout << "MOVE " << dishPosXY.first << " " << dishPosXY.second << std::endl;
        return false;
    }
    else {
        std::cout << "USE " << dishPosXY.first << " " << dishPosXY.second << std::endl;
        return false;
    }
    return true;
}
#pragma endregion maker

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    customer client;
    kitchen cookhouse;
    player me, partner;

    int num_all_customers;
    std::cin >> num_all_customers;
    client.setNum(num_all_customers);
    for (int i = 0; i < num_all_customers; i++) {
        std::string customer_item;
        int customer_award;
        std::cin >> customer_item >> customer_award;
        client.addItemAward(customer_item, customer_award);
    }
    std::cin.ignore();
    for (int i = 0; i < 7; i++) {
        std::string kitchen_line;
        getline(std::cin, kitchen_line);
        cookhouse.addMaze(kitchen_line);
    }

    std::string dish = client.chooseDish();
    maker cook;

    while (1) {
        int turns_remaining;
        std::cin >> turns_remaining;
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
        for (int i = 0; i < num_tables_with_items; i++) {
            int table_x, table_y;
            std::string item;
            std::cin >> table_x >> table_y >> item;
            cookhouse.setTableInfo(table_x, table_y, item);
        }
        std::string oven_contents;
        int oven_timer;
        std::cin >> oven_contents >> oven_timer;
        int num_customers;
        std::cin >> num_customers;
        client.setNum(num_customers);
        client.clearItemAward();
        for (int i = 0; i < num_customers; i++) {
            std::string customer_item;
            int customer_award;
            std::cin >> customer_item >> customer_award;
            client.addItemAward(customer_item, customer_award);
        }
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        // MOVE x y // USE x y // WAIT
        if(cook.startMake(dish, cookhouse, me)) {
            dish = client.chooseDish();
        }
    }
}