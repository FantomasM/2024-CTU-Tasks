//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_ARCHETYPE_H

#include "ItemFactory_effects.h"

#define SEMESTRAL_WORK_ARCHETYPE_H

class Archetype {
public:
    Archetype(std::string name) : class_name(std::move(name)) {}

    Archetype();

    bool operator==(const Archetype &second) const;

    bool operator!=(const Archetype &second) const;

    bool from_json(nlohmann::json jsonData);

    void Print(std::ostream &os);

    Archetype &operator=(const Archetype &second);

    shared_ptr<Effect> find_effect(const string &name);

    std::string class_name;
    std::vector<std::shared_ptr<Effect>> effects;
};

#endif //SEMESTRAL_WORK_ARCHETYPE_H
