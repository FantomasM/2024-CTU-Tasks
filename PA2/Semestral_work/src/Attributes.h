//
// Created by fantomasm on 3.5.23.
//

#ifndef UNTITLED8_ATTRIBUTES_H
#define UNTITLED8_ATTRIBUTES_H

#include "Skill.h"
#include <json.hpp>
#include <iostream>
#include <ncurses.h>
#include <utility>

class Attributes {
public:
    Attributes();

    Attributes(const Attributes &second);

    ~Attributes();

    bool Has_such_skill(const Skill &ski) const;

    bool Has_such_skills(const Attributes &second) const;

    void Print_to_screen();

    void Print(std::ostream &os);

    nlohmann::json toJson() const;

    void fromJson(const nlohmann::json &);

    bool activate_bonus_int(const Skill &ski, int increase_Mod);

    bool use_free_points(int choice);


    void read_skills_from_json_file(const std::string &filename);

    size_t skills_count();

    int points_to_distribute = 5;
private:


    std::vector<Skill> skills;

};

#endif //UNTITLED8_ATTRIBUTES_H
