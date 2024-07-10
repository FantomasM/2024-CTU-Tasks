//
// Created by fantomasm on 28.5.23.
//


#ifndef SEMESTRAL_WORK_ITEMFACTORY_EFFECTS_H
#define SEMESTRAL_WORK_ITEMFACTORY_EFFECTS_H

#include "StatMod.h"
#include "Healing.h"
#include "Massive_attack.h"
#include "Paralysing.h"
#include "Regeneration.h"
#include "berserk.h"
//Factory class to read Effect elements from json files
using EffectPtr = std::shared_ptr<Effect>;

class ItemFactory_effects {
public:
    static EffectPtr create(const std::string &class_name);
};

#endif //SEMESTRAL_WORK_ITEMFACTORY_EFFECTS_H
