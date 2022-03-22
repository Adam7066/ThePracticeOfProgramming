#include <iostream>
#include "kitchen.h"
#include "customer.h"
#include "maker.h"
#include "player.h"
#include "tool.h"

// "WINDOW", "DISH", "ICE_CREAM", "BLUEBERRIES",
// "STRAWBERRIES", "CHOPPED", "Dough", "OVEN", "CROISSANT"

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
            cook.startMake(dish, cookhouse, me);
        }
    }
}