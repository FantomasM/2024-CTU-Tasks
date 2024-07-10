//
// Created by fantomasm on 28.5.23.
//

#include "ItemFactory.h"

ItemPtr ItemFactory::create(const std::string &class_name) {

    static std::unordered_map<std::string, std::function<ItemPtr()>> constructors = {
            {"Weapon",     []() { return std::make_shared<Weapon>(); }},
            {"Armour",     []() { return std::make_shared<Armour>(); }},
            {"Food",       []() { return std::make_shared<Food>(); }},
            {"Valuables",  []() { return std::make_shared<Valuables>(); }},
            {"Item_saver", []() { return std::make_shared<Item_saver>(); }}


    };

    auto it = constructors.find(class_name);
    if (it != constructors.end()) {
        return it->second();
    } else {
        return nullptr;
    }

}