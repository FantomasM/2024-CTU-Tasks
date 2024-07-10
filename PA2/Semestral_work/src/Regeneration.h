//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_REGENERATION_H
#define SEMESTRAL_WORK_REGENERATION_H

#include "Passive_Effect.h"

class Regeneration : public Passive_Effect {
public:
    Regeneration() = default;

    int heal_effect = 1;

    void apply_effect(vector<shared_ptr<Character>> &Char) override;

    nlohmann::json to_json() override;

    void from_json(nlohmann::json effect) override;

    void Print(std::ostream &os) override;
};

#endif //SEMESTRAL_WORK_REGENERATION_H
