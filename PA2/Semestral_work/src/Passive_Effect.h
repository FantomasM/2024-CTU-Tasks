//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_PASSIVE_EFFECT_H
#define SEMESTRAL_WORK_PASSIVE_EFFECT_H

#include "Effect.h"

class Passive_Effect : public Effect {
public:
    Passive_Effect() : Effect() { active = false; }

    bool activated = false;
    bool first_print = true;

};

#endif //SEMESTRAL_WORK_PASSIVE_EFFECT_H
