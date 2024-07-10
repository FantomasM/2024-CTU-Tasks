//
// Created by fantomasm on 28.5.23.
//

#include "Food.h"

void Food::Print(std::ostream &os) {
    Item::Print(os);
    os << "Heal effect is " << heal_effect << std::endl;
}

nlohmann::json Food::to_json() const {
    nlohmann::json jsonItem = Item::to_json();
    jsonItem["heal_effect"] = heal_effect;
    return jsonItem;
}

void Food::from_json(nlohmann::json jsonItem) {

    Item::from_json(jsonItem);
    heal_effect = jsonItem["heal_effect"];


}

int Food::get_info() const {
    return heal_effect;

}

std::string Food::get_class_name() const {

    return class_name;

}