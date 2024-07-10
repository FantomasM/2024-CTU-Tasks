//
// Created by fantomasm on 28.5.23.
//

#include "Skill.h"

nlohmann::json Skill::toJson() const {
    nlohmann::json perk;
    perk["name"] = name;
    perk["level"] = level;
    perk["cost_next_level"] = cost_next_level;
    perk["max_level"] = max_level;
    return perk;
}

bool Skill::operator==(const Skill &skill) const {
    if (name == skill.name
            ) {
        return true;
    }
    return false;
}

void Skill::increase_level() {

    if (level != max_level) {
        level++;
        //increasing cost of next level when user reached 50% of max level or 75%
        if (max_level / 2 == level || (max_level / 2 + max_level / 4) == level) {
            cost_next_level *= 2;
        }
    }

}

Skill Skill::fromJson(nlohmann::json skill) {
    return {skill["name"], skill["level"], skill["cost_next_level"], skill["max_level"]};
}

Skill &Skill::operator=(const Skill &skill) {
    name = skill.name;
    level = skill.level;
    cost_next_level = skill.cost_next_level;
    max_level = skill.max_level;
    return *this;
}
