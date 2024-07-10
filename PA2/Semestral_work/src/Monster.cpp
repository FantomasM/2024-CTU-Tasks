//
// Created by fantomasm on 23.5.23.
//
#include <random>
#include "Monster.h"

//Interaction with user, if not paralyzed, monster will deal random damage
bool Monster::Interaction(vector<shared_ptr<Character>> &monsters) {
    if (!Paralysed) {
        std::random_device rd;
        std::mt19937 gen(rd());


        std::uniform_int_distribution<int> distribution(damage, damageMax);


        int randomNumber = distribution(gen);
        if (monsters.size() >= 3) {
            monsters[1]->TakeDamage(randomNumber);
            printw("Monster %s dealt you %d damage \n", name.c_str(),
                   static_cast<int>(randomNumber * (1 - (monsters[1]->get_defence() * 0.01))));
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            Inventory_use();

            return true;
        } else {
            return false;
        }

    }

    printw("Monster %s is paralyzed on this turn \n", name.c_str());
    refresh();
    Paralysed = false;
    return true;


}

void Monster::Load_character_json_opened(const nlohmann::json &json) {
    Character::Load_character_json_opened(json);
    damageMax = json["damageMax"];
}

void Monster::Save_character_json_opened(nlohmann::json &json) {
    Character::Save_character_json_opened(json);
    json["damageMax"] = damageMax;
}

bool Monster::operator==(const Monster &other) {


    if (name == other.name && level == other.level) {
        return true;
    }
    return false;

}