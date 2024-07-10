//
// Created by fantomasm on 28.5.23.
//

#include "berserk.h"

nlohmann::json berserk::to_json() {
    nlohmann::json effect;
    effect = Effect::to_json();
    effect["increase_Mod"] = increase_Mod;
    effect["measure"] = measure;
    return effect;

}

void berserk::from_json(nlohmann::json effect) {
    Effect::from_json(effect);
    increase_Mod = effect["increase_Mod"];
    measure = effect["measure"];
}

void berserk::apply_effect(vector<shared_ptr<Character>> &Char) {
    if (Char[0]->get_HP() <= Char[0]->get_MaxHP() * measure && !activated) {
        Char[0]->Change_Damage(increase_Mod);
        activated = true;
        return;
    }
    if (activated && Char[0]->get_HP() > Char[0]->get_MaxHP() * measure) {
        Char[0]->Change_Damage(Char[0]->get_def_damage());
    }

}

void berserk::Print(std::ostream &os) {
    if (first_print) {
        Effect::Print(os);
        os << "increase mod is " << increase_Mod << endl;
    }
    first_print = false;
}
