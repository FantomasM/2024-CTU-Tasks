//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_HEALING_H
#define SEMESTRAL_WORK_HEALING_H

#include "Active_Effect.h"

class Healing : public Active_Effect {
public:
    Healing() = default;

    void apply_effect(vector<shared_ptr<Character>> &Char) override;

    void Print(std::ostream &os) override {
        Effect::Print(os);
        os << "Restore up to " << heal_effect << " health points" << endl;

    }

    int heal_effect = 1;

    nlohmann::json to_json() override;

    void from_json(nlohmann::json effect) override;
};

#endif //SEMESTRAL_WORK_HEALING_H
