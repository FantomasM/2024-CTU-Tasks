//
// Created by fantomasm on 28.5.23.
//

#include "Armour_cont.h"

bool Armour_cont::Add_Item(std::shared_ptr<Item> &item) {


    int pos = 0;
    for (const auto &ITEM: items) {
        if (ITEM->get_class_name().back() == item->get_class_name().back()) {
            std::shared_ptr<Item> tmp = ITEM;
            items.erase(items.begin() + pos);

            items.emplace_back(item);
            item.reset();
            item = tmp;
            return false;
        }
        pos++;
    }
    num_of_items++;
    items.emplace_back(item);
    return true;


}

std::string Armour_cont::get_class_name() {
    return Class_name;
}

bool Armour_cont::Remove_Item(const std::shared_ptr<Item> &item) {
    std::string name = "Armour";
    if (item->get_class_name().rfind(name, 0) == 0 && item->get_class_name().back() >= '0' &&
        item->get_class_name().back() <= '5') {
        size_t pos = 0;
        for (const auto &ITEM: items) {
            if (ITEM->get_class_name().back() == item->get_class_name().back()) {
                items.erase(items.begin() + static_cast<int>(pos));
                num_of_items--;
                return true;
            }
            pos++;
        }

        return false;


    } else {


        return false;
    }
}