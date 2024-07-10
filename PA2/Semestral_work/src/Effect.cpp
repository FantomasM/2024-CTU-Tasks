//
// Created by fantomasm on 3.5.23.
//

#include "Effect.h"

nlohmann::json Effect::to_json() {
    nlohmann::json effect;

    effect["name of effect"] = name_of_effect;
    effect["Class name"] = Class_name;
    return effect;
}

void Effect::from_json(nlohmann::json effect) {

    name_of_effect = effect["name_of_effect"];
    Class_name = effect["class_name"];


}

