//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_SKILL_H
#define SEMESTRAL_WORK_SKILL_H

#include "json.hpp"
#include "iostream"

class Skill {
public:
    Skill() : name("Default_skill"), level(0), cost_next_level(1), max_level(10) {}

    Skill(std::string Name, int Level, int Cost_next_Level, int Max_level) : name(std::move(Name)), level(Level),
                                                                             cost_next_level(Cost_next_Level),
                                                                             max_level(Max_level) {}

    Skill &operator=(const Skill &skill);

    Skill(const Skill &other) : name(other.name), level(other.level), cost_next_level(other.cost_next_level),
                                max_level(other.max_level) {}

    bool operator==(const Skill &skill) const;

    std::string name;
    int level;

    void increase_level();

    int cost_next_level = 0;
    int max_level = 0;

    nlohmann::json toJson() const;

    Skill fromJson(nlohmann::json);

};

#endif //SEMESTRAL_WORK_SKILL_H
