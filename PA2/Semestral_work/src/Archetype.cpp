//
// Created by fantomasm on 28.5.23.
//

#include "Archetype.h"

//Converting from json
bool Archetype::from_json(nlohmann::json jsonData) {
    //In case of empty effects, file must be wrong, because archetype cant be without  effects
    if (!jsonData["effects"].is_null() && !jsonData["effects"].empty()) {
        for (const auto &type: jsonData["effects"]) {
            std::string className = type["class_name"];
            EffectPtr obj = ItemFactory_effects::create(className);
            obj->from_json(type);
            effects.push_back(obj);

        }
        return true;
    } else {
        return false;
    }
}

bool Archetype::operator==(const Archetype &second) const {

    if (class_name == second.class_name && effects == second.effects) {
        return true;
    }
    return false;

}

bool Archetype::operator!=(const Archetype &second) const {

    return !(*this == second);


}

void Archetype::Print(std::ostream &os) {

    os << class_name << std::endl << std::endl;
    for (const auto &ef: effects) {

        ef->Print(os);
    }
    os << std::endl;

}

Archetype &Archetype::operator=(const Archetype &second) {

    if (*this != second) {
        effects = second.effects;
        class_name = second.class_name;
    }
    return *this;

}

Archetype::Archetype() = default;

shared_ptr<Effect> Archetype::find_effect(const std::string &name) {
    //Trivial finding effects, there are only 6 effects and that's why there is no need to use better solution
    for (const auto &eff: effects) {
        if (eff->name_of_effect == name) {
            //find effect is used only for finding active effects, so passive effect is a wrong result
            if (!eff->active) {
                return nullptr;
            }
            return eff;
        }
    }
    return nullptr;
}