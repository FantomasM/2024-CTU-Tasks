//
// Created by fantomasm on 23.5.23.
//

#ifndef SEMESTRAL_WORK_NORMAL_NPC_H
#define SEMESTRAL_WORK_NORMAL_NPC_H

#include "Task.h"
#include "Dialogue_manager.h"
#include "Character.h"

class Normal_NPC : public Character {

public:
    Normal_NPC() : Character() { class_name = "Normal_NPC"; }

    Normal_NPC(short int Level, Attributes &Perks, int Damage, int Defence, int hp, int hpmax, string Name) : Character(
            Level, Perks, Damage, Defence, hp, hpmax, std::move(Name)) { class_name = "Normal_NPC"; }

    bool Interaction(vector<shared_ptr<Character>> &monsters) override;


    void Market(shared_ptr<Character> &person) override;

    void Print_tasks(std::ostream &os) override;

    void Tasks(std::shared_ptr<Character> &person);

    bool Save_character_json(string filename) override;

    void Save_character_json_opened(nlohmann::json &json) override;

    bool Load_character_json(std::string Filename) override;

    void Load_character_json_opened(const nlohmann::json &json) override;

    inline void Dialogue_interaction();

    void Print(std::ostream &os) override;

private:
    std::string Description = "Default";
    std::shared_ptr<Dialogue_manager> manager = make_shared<Dialogue_manager>();

    vector<Task> tasks;
};

#endif //SEMESTRAL_WORK_NORMAL_NPC_H
