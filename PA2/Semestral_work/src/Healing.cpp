//
// Created by fantomasm on 28.5.23.
//

#include "Healing.h"

nlohmann::json Healing::to_json() {
    nlohmann::json effect;
    effect = Effect::to_json();
    effect["heal_effect"] = heal_effect;
    return effect;

}

void Healing::from_json(nlohmann::json effect) {
    Effect::from_json(effect);
    heal_effect = effect["heal_effect"];
}

void Healing::apply_effect(vector<shared_ptr<Character>> &Char) {
    if (Char.size() > 1) {
        Char[1]->Heal(heal_effect);
        printw("You healed yourself and now your HP is %d of %d\n", Char[1]->get_HP(), Char[1]->get_MaxHP());
    }
}