//
// Created by fantomasm on 24.5.23.
//




#ifndef SEMESTRAL_WORK_TASK_H
#define SEMESTRAL_WORK_TASK_H

#include <utility>
#include "Character.h"

class Task {
public:
    Task() : Task_name("Default"), Task_description("Default task"), type(Default) {}

    Task(string name, string description, shared_ptr<Character> person, vector<Skill> &skills) : Task_name(
            std::move(name)), Task_description(std::move(description)), skills_for_task(skills), person_to_find(
            std::move(person)) { type = Type_NPC; }

    Task(string name, string description, shared_ptr<Item> person, vector<Skill> &skills) : Task_name(std::move(name)),
                                                                                            Task_description(std::move(
                                                                                                    description)),
                                                                                            skills_for_task(skills),
                                                                                            item_to_find(std::move(
                                                                                                    person)) { type = Type_item; }

    Task(string name, string description, shared_ptr<Character> person, int num, vector<Skill> &skills) : Task_name(
            std::move(name)), Task_description(std::move(description)), skills_for_task(skills), monster_to_find(
            std::move(person)) { type = Type_monster; }

    bool Control_task(const shared_ptr<Character> &NPC);

    bool Control_task(const shared_ptr<Item> &item);

    bool Get_reward(shared_ptr<Character> &user);

    bool Enough_skills(const Attributes &skills);


    vector<shared_ptr<Item>> Get_reward(int &Award);

    void Print(std::ostream &os) const;

    bool from_json(const nlohmann::json &json);

    nlohmann::json to_json() const;

    bool Finished = false;
    string Task_name;
    string Task_description;
    int award = 0;
    vector<Skill> skills_for_task;
    vector<shared_ptr<Item>> prizes;
    Type type;
    shared_ptr<Character> person_to_find = nullptr;
    shared_ptr<Item> item_to_find = nullptr;
    shared_ptr<Character> monster_to_find = nullptr;

    bool operator==(const Task &other) const;


};

#endif //SEMESTRAL_WORK_TASK_H
