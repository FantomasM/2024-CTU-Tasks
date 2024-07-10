//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_PARALYSING_H
#define SEMESTRAL_WORK_PARALYSING_H

#include "Active_Effect.h"

class Paralysing : public Active_Effect {
public:
    Paralysing() = default;

    void apply_effect(vector<shared_ptr<Character>> &Char) override;


    void Print(std::ostream &os) override {
        Effect::Print(os);
        os << "paralyzes " << count_of_persons << " persons" << std::endl;

    }

    int count_of_persons = 1;

    nlohmann::json to_json() override;

    void from_json(nlohmann::json effect) override;

};

#endif //SEMESTRAL_WORK_PARALYSING_H
