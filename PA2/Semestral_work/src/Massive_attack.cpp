//
// Created by fantomasm on 28.5.23.
//

#include "Massive_attack.h"

nlohmann::json Massive_attack::to_json() {
    nlohmann::json effect;
    effect = Effect::to_json();
    effect["damage"] = damage;
    return effect;
}

void Massive_attack::apply_effect(vector<shared_ptr<Character>> &Char) {
    for (size_t i = 2; i < Char.size(); i++) {
        Char[i]->TakeDamage(damage);
        printw("You dealt %d damage to %s\n", static_cast<int>(damage * (1 - (Char[i]->get_defence() * 0.01))),
               Char[i]->get_name().c_str());
        if (Char[i]->get_HP() == 0) {
            Char.erase(Char.begin() + static_cast<int>(i));
        }
    }
}

void Massive_attack::from_json(nlohmann::json effect) {
    Effect::from_json(effect);
    damage = effect["damage"];
}