//
// Created by fantomasm on 28.5.23.
//

#include "Regeneration.h"

nlohmann::json Regeneration::to_json() {
    nlohmann::json effect;
    effect = Effect::to_json();
    effect["heal_effect"] = heal_effect;
    return effect;

}

void Regeneration::from_json(nlohmann::json effect) {
    Effect::from_json(effect);
    heal_effect = effect["heal_effect"];
}

void Regeneration::apply_effect(vector<shared_ptr<Character>> &Char) {
    Char[0]->Heal(heal_effect);


}

void Regeneration::Print(std::ostream &os) {
    if (first_print) {
        Effect::Print(os);
        os << "heal effect is " << heal_effect << endl;
    }
    first_print = false;

}