//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_BERSERK_H
#define SEMESTRAL_WORK_BERSERK_H

#include "Passive_Effect.h"

class berserk : public Passive_Effect {
public:
    berserk() = default;

    int increase_Mod = 2;
    double measure = 0.3;

    void apply_effect(vector<shared_ptr<Character>> &Char) override;

    nlohmann::json to_json() override;

    void from_json(nlohmann::json effect) override;

    void Print(std::ostream &os) override;
};

#endif //SEMESTRAL_WORK_BERSERK_H
