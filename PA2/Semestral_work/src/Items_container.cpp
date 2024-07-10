//
// Created by fantomasm on 4.5.23.
//
#include <thread>
#include "Items_container.h"

#define Item_saver_backpack 2
#define Backpack_item_saver 1
#define Back 3

Items_container::Items_container() : capacity(10), num_of_items(0) {
    items.reserve(10);
}

Items_container::~Items_container() {
    items.clear();
}

bool Items_container::Add_Item(std::shared_ptr<Item> &item) {
    if (num_of_items < capacity) {
        items.push_back(item);
        num_of_items++;
        return true;
    } else {

        return false;
    }
}

std::shared_ptr<Item> Items_container::find_ref(const std::string &name) {
    for (auto &it: items) {
        if (it->Item_name == name) {
            return it;
        }
    }

    return nullptr;

}

//Methods for printing specific type of item
bool Items_container::Print_Item_savers(std::ostream &os) {
    for (const auto &item: items) {
        if (item->IsItemSaver()) {
            item->Print(os);
        }
    }
    if (os.fail()) {
        return false;
    }
    return true;
}

void Items_container::Print_Weapons(std::ostream &os) {
    for (const auto &it: items) {
        if (it->IsWeapon()) {
            it->Print(os);
        }
    }
}

void Items_container::Print_Armour(std::ostream &os) {
    for (const auto &it: items) {
        if (it->IsArmour()) {
            it->Print(os);
        }
    }
}

bool Items_container::Remove_Item(const std::shared_ptr<Item> &item) {
    for (size_t i = 0; i < items.size(); i++) {
        if (*(items[i]) == *(item)) {
            items.erase(items.begin() + static_cast<int>(i));
            num_of_items--;
            return true;
        }
    }
    throw std::runtime_error("No such item in inventory");

}

void Items_container::Print_Items(std::ostream &os) {
    os << name_of_container << std::endl;
    os << "capacity is " << capacity << " and " << items.size() << " places are occupied" << std::endl;
    for (const auto &ITEM: items) {
        if (ITEM) {
            ITEM->Print(os);
        }
    }
    os << std::endl;
}

void Items_container::Print_heal_items(std::ostream &os) {
    for (const auto &it: items) {
        if (it->IsHealingItem()) {
            it->Print(os);
        }
    }
}

//Method for monsters to use any heal item they have
std::shared_ptr<Item> Items_container::find_any_heal_item() {
    for (auto &item: items) {
        if (item->IsHealingItem()) {
            return item;
        }
    }
    return nullptr;
}

int Items_container::delete_heal_item(const std::string &name) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i]->IsHealingItem() && items[i]->Item_name == name) {
            int num = items[i]->get_info();
            items.erase(items.begin() + static_cast<int>(i));
            return num;
        }
    }
    return 0;
}

nlohmann::json Items_container::convertToJson() {
    nlohmann::json jsonItems;
    jsonItems["Class name"] = get_class_name();
    jsonItems["Capacity"] = capacity;
    jsonItems["Number of Items"] = items.size();
    jsonItems["Items"] = nullptr;
    for (const auto &item: items) {
        nlohmann::json jsonItem;


        jsonItems["Items"].push_back(item->to_json());
    }

    return jsonItems;
}

bool Items_container::empty() const {

    return items.empty();

}

bool Items_container::full() const {

    if (capacity == num_of_items) {
        return true;
    }
    return false;

}

std::shared_ptr<Item> Items_container::Find_item(const std::string &name) {
    for (auto &it: items) {
        if (it->Item_name == name) {
            return it;
        }
    }
    return nullptr;
}


