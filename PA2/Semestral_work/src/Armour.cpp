//
// Created by fantomasm on 28.5.23.
//
#include "Armour.h"

void Armour::Print(std::ostream &os) {
    Item::Print(os);
    os << "Defence is " << defence << std::endl;
}

nlohmann::json Armour::to_json() const {
    nlohmann::json jsonItem = Item::to_json();
    jsonItem["Class_name"] = class_name;
    jsonItem["defence"] = defence;
    jsonItem["Part"] = Part;
    return jsonItem;
}

void Armour::from_json(nlohmann::json jsonItem) {

    Item::from_json(jsonItem);
    defence = jsonItem["defence"];
    Part = jsonItem["Part"];

}

int Armour::get_info() const {

    return defence;

}

std::string Armour::get_class_name() const {
    //get class_name is returning class_name and number of part of armour for checking if such type of armour is already on you
    return class_name + std::to_string(static_cast<int>(Part));

}