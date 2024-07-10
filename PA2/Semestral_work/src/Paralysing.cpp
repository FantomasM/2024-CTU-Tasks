//
// Created by fantomasm on 28.5.23.
//

#include "Paralysing.h"

nlohmann::json Paralysing::to_json() {
    nlohmann::json effect;
    effect = Effect::to_json();
    effect["count_of_persons"] = count_of_persons;
    return effect;

}

void Paralysing::from_json(nlohmann::json effect) {
    Effect::from_json(effect);
    count_of_persons = effect["count_of_persons"];
}

void Paralysing::apply_effect(vector<shared_ptr<Character>> &Char) {
    for (size_t i = 2; i < Char.size() || i < static_cast<size_t>(count_of_persons); i++) {
        Char[i]->Paralysed = true;
        printw("%s is now paralyzed\n", Char[i]->get_name().c_str());
    }


}