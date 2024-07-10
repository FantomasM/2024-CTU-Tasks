//
// Created by fantomasm on 4.5.23.
//

#ifndef UNTITLED8_INVENTORY_H
#define UNTITLED8_INVENTORY_H

#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include "ItemFactory.h"

#define Left_arm 0
#define Right_arm 1
#define Armour_container 2
#define Backpack_cont 3


class Items_container {
public:
    inline Items_container(int Capacity) : capacity(Capacity), num_of_items(0) {
        items.reserve(Capacity);
    }

    Items_container();

    ~Items_container();

    virtual bool Add_Item(std::shared_ptr<Item> &item);

    virtual bool Remove_Item(const std::shared_ptr<Item> &item);

    bool Print_Item_savers(std::ostream &os);

    std::shared_ptr<Item> find_ref(const std::string &name);

    void Print_Items(std::ostream &os);

    virtual nlohmann::json convertToJson();

    virtual std::string get_class_name() = 0;

    const std::string Class_name = "Inventory";

    void Print_heal_items(std::ostream &os);

    int delete_heal_item(const std::string &name);

    bool empty() const;

    bool full() const;

    std::shared_ptr<Item> Find_item(const std::string &name);

    void Print_Weapons(std::ostream &os);

    void Print_Armour(std::ostream &os);

    std::shared_ptr<Item> find_any_heal_item();

    int capacity;
    int num_of_items;
protected:
    std::string name_of_container;

    std::vector<std::shared_ptr<Item>> items;
};


#endif //UNTITLED8_INVENTORY_H
