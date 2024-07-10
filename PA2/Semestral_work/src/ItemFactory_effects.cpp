//
// Created by fantomasm on 28.5.23.
//

#include "ItemFactory_effects.h"

EffectPtr ItemFactory_effects::create(const std::string &class_name) {

    static std::unordered_map<std::string, std::function<EffectPtr()>> constructors = {
            {"Paralysing",     []() { return std::make_shared<Paralysing>(); }},
            {"Healing",        []() { return std::make_shared<Healing>(); }},
            {"Massive_attack", []() { return std::make_shared<Massive_attack>(); }},
            {"StatMod",        []() { return std::make_shared<StatMod>(); }},
            {"Regeneration",   []() { return std::make_shared<Regeneration>(); }},
            {"berserk",        []() { return std::make_shared<berserk>(); }}


    };

    auto it = constructors.find(class_name);
    if (it != constructors.end()) {
        return it->second();
    } else {
        return nullptr;
    }

}