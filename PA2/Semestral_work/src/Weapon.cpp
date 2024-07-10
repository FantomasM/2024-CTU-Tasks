//
// Created by fantomasm on 28.5.23.
//

#include "Weapon.h"

void Weapon::Print(std::ostream &os) {
    Item::Print(os);
    os << "Damage is " << damage << std::endl;
}

nlohmann::json Weapon::to_json() const {
    nlohmann::json jsonItem = Item::to_json();
    jsonItem["damage"] = damage;
    return jsonItem;
}

void Weapon::from_json(nlohmann::json jsonItem) {

    Item::from_json(jsonItem);
    damage = jsonItem["damage"];

}

int Weapon::get_info() const {

    return damage;

}

std::string Weapon::get_class_name() const {

    return class_name;

}