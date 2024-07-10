//
// Created by fantomasm on 28.5.23.
//

#include "Character_arm.h"

bool Character_arm::Remove_Item(const std::shared_ptr<Item> &item) {
    if (*items[0] == *item) {
        items.erase(items.begin());
        num_of_items--;
        return true;
    }
    return false;
}

bool Character_arm::Add_Item(std::shared_ptr<Item> &item) {

    if (items.empty()) {
        items.push_back(item);
        num_of_items++;
        return true;
    }
    std::shared_ptr<Item> tmp = items[0];
    items.clear();
    items.push_back(item);
    item.reset();
    item = tmp;
    return false;
}

std::string Character_arm::get_class_name() {
    return Class_name;
}