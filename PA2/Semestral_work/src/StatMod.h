//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_STATMOD_H
#define SEMESTRAL_WORK_STATMOD_H

#include "Passive_Effect.h"

class StatMod : public Passive_Effect {
public:
    StatMod() = default;

    Skill stat;
    int increase_Mod = 3;

    void apply_effect(vector<shared_ptr<Character>> &Char) override;

    nlohmann::json to_json() override;

    void from_json(nlohmann::json effect) override;

    void Print(std::ostream &os) override;

};

#endif //SEMESTRAL_WORK_STATMOD_H
