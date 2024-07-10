//
// Created by fantomasm on 3.5.23.
//
#include <iostream>
#include <fstream>
#include "Attributes.h"


void Attributes::Print(std::ostream &os) {
    for (const auto &ski: skills) {
        os << ski.name << " level: " << ski.level << " cost of next level " << ski.cost_next_level << " max level is "
           << ski.max_level << std::endl;
    }
    os << "Point to distribute : " << points_to_distribute << std::endl;
}

Attributes::Attributes() : points_to_distribute(5) {}

Attributes::Attributes(const Attributes &second) : points_to_distribute(second.points_to_distribute),
                                                   skills(second.skills) {}

nlohmann::json Attributes::toJson() const {
    nlohmann::json perks;

    for (const auto &ski: skills) {

        perks.push_back(ski.toJson());
    }
    return perks;

}

void Attributes::fromJson(const nlohmann::json &Skills) {
    skills.clear();


        for (const auto &ski: Skills) {
            skills.push_back(Skill(ski["name"], ski["level"], ski["cost_next_level"], ski["max_level"]));
        }
    }


//Method for activating passive effect's bonuses
bool Attributes::activate_bonus_int(const Skill &ski, int increase_Mod) {

    for (auto &skill: skills) {
        if (ski.name == skill.name) {
            skill.level += increase_Mod;

            return true;
        }

    }

    return false;

}

//Method for using free points
bool Attributes::use_free_points(int choice) {
    //return false if there are no free points
    if (points_to_distribute <= 0) {

        return false;
    }
    if (choice > static_cast<int>(skills.size()) - 1 || choice < 0) {
        //do nothing if choice is out of bounds

        return true;
    } else {
        //If skill exists and user have enough points then increase this skill
        if (skills[choice].cost_next_level <= points_to_distribute) {
            points_to_distribute -= skills[choice].cost_next_level;
            skills[choice].increase_level();
            return true;
        }
            //if user don't have enough points , return false
        else {
            return false;
        }


    }

}

size_t Attributes::skills_count() {

    return skills.size();

}

//Checking if attributes has such skill on same level or better
//Needed for basic checks and check for tasks
bool Attributes::Has_such_skill(const Skill &ski) const {
    bool found = std::any_of(skills.begin(), skills.end(), [&](const Skill &Ski) {
        return (Ski.name == ski.name) && (Ski.level >= ski.level);
    });
    return found;

}

//Same but checking all skills of second Attributes
bool Attributes::Has_such_skills(const Attributes &second) const {

    bool allSkillsExist = std::all_of(skills.begin(), skills.end(), [&](const Skill &Ski) {
        return second.Has_such_skill(Ski);
    });
    return allSkillsExist;
}

void Attributes::Print_to_screen() {
    size_t i = 1;

    for (const auto &ski: skills) {
        printw("%zu: Skill %s Level %d Points for next level %d Max. Level %d \n", i, ski.name.c_str(), ski.level,
               ski.cost_next_level, ski.max_level);
        i++;
    }
}

Attributes::~Attributes() = default;

void Attributes::read_skills_from_json_file(const std::string &filename) {
    std::ifstream new_file;

    new_file.open(filename, std::ios::in);

    if (!new_file.is_open()) {

        throw std::runtime_error("Failed to open file: " + filename);

    } else {
        skills.clear();
        nlohmann::json jsonData;
        new_file >> jsonData;
        points_to_distribute = jsonData["points_to_distribute"];
        if (!jsonData["skills"].is_null()) {
            for (const auto &ski: jsonData["skills"]) {
                skills.push_back(Skill(ski["name"], ski["level"], ski["cost_next_level"], ski["max_level"]));
            }
        }
    }
}
