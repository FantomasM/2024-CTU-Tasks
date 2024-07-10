//
// Created by fantomasm on 28.5.23.
//


#ifndef SEMESTRAL_WORK_INVENTORY_H
#define SEMESTRAL_WORK_INVENTORY_H

#include "thread"
#include "Character_arm.h"
#include "Backpack.h"
#include "Armour_cont.h"

class Inventory {
public:
    inline Inventory() {
        Inv.reserve(4);
        Inv.emplace_back(std::make_shared<Character_arm>("Left Hand"));
        Inv.emplace_back(std::make_shared<Character_arm>("Right Hand"));
        Inv.emplace_back(std::make_shared<Armour_cont>("Your Armour"));
        Inv.emplace_back(std::make_shared<Backpack>("Base_Backpack"));
    }

    std::vector<std::shared_ptr<Items_container>> Inv;

    void Print(std::ostream &os);

    bool Print(std::ostream &os, int num);

    bool Put_in_left_hand(std::shared_ptr<Item> &item);

    bool Put_in_Right_hand(std::shared_ptr<Item> &item);

    bool Put_on_armour(std::shared_ptr<Item> &item);

    bool Put_in_backpack(std::shared_ptr<Item> &item);

    bool Item_saver_use();

    bool Print_Weapons_Backpack(std::ostream &os);

    bool Print_Weapons_Arms(std::ostream &os);

    bool Print_Armour_Backpack(std::ostream &os);

    bool Print_heal_items(std::ostream &os);

    void Inside_item_saver(std::shared_ptr<Item> &item_saver);

    void item_saver_backpack(std::shared_ptr<Item> &item_saver);

    void backpack_item_saver(std::shared_ptr<Item> &item_saver);

    bool Delete_Item(const std::shared_ptr<Item> &item, int num);

    int free_places(int num);

    bool Use_heal_item(const std::string &name, int &heal_effect);

    bool Full(int num);

    int Use_any_heal_item();

    std::shared_ptr<Item> find_item(const std::string &name, int num);

    std::shared_ptr<Item> find_ref(const std::string &name, int num);


};

#endif //SEMESTRAL_WORK_INVENTORY_H
