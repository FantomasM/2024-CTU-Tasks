//
// Created by fantomasm on 28.5.23.
//

#include "StatMod.h"

nlohmann::json StatMod::to_json() {
    nlohmann::json effect;
    effect = Effect::to_json();
    effect["stat"] = stat.name;
    effect["increase_Mod"] = increase_Mod;
    return effect;
}

void StatMod::from_json(nlohmann::json effect) {
    Effect::from_json(effect);
    string name = effect["stat"];
    stat = Skill(name, 1, 1, 1);
    increase_Mod = effect["increase_Mod"];
}

void StatMod::apply_effect(vector<shared_ptr<Character>> &Char) {

    if (!activated) {
        Char[0]->Increase_stat(stat, increase_Mod);
    }
    activated = true;
}

void StatMod::Print(std::ostream &os) {

    if (first_print) {
        Effect::Print(os);
        os << "name of stat is " << stat.name << " and increase mod is " << increase_Mod << endl;
    }
    first_print = false;

}