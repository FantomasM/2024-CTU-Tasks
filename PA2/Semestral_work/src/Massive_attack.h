//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_MASSIVE_ATTACK_H
#define SEMESTRAL_WORK_MASSIVE_ATTACK_H

#include "Active_Effect.h"

class Massive_attack : public Active_Effect {
public:
    Massive_attack() = default;

    void apply_effect(vector<shared_ptr<Character>> &Char) override;

    void Print(std::ostream &os) override {
        Effect::Print(os);
        os << "Deal " << damage << " to all monsters" << std::endl;

    }

    int damage = 1;

    nlohmann::json to_json() override;

    void from_json(nlohmann::json effect) override;
};

#endif //SEMESTRAL_WORK_MASSIVE_ATTACK_H
