//
// Created by fantomasm on 23.5.23.
//

#ifndef SEMESTRAL_WORK_MONSTER_H
#define SEMESTRAL_WORK_MONSTER_H

#include "Character.h"
#include "Effect.h"

class Monster : public Character {
public:
    Monster() : Character() { class_name = "Monster"; }

    Monster(short int Level, Attributes &Perks, int Damage, int Defence, int hp, int hpmax, string Name) : Character(
            Level, Perks, Damage, Defence, hp, hpmax, std::move(Name)) { class_name = "Monster"; }

    Monster(short int Level, Attributes &Perks, int Damage, int maxDmg, int Defence, int hp, int hpmax, string Name)
            : Character(Level, Perks, Damage, Defence, hp, hpmax, std::move(Name)),
              damageMax(maxDmg) { class_name = "Monster"; }

    bool Interaction(vector<shared_ptr<Character>> &monsters) override;

    bool operator==(const Monster &other);

    void Save_character_json_opened(nlohmann::json &json) override;

    void Load_character_json_opened(const nlohmann::json &json) override;

private:
    int damageMax = 100;

};

#endif //SEMESTRAL_WORK_MONSTER_H
