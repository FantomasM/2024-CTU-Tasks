//
// Created by fantomasm on 3.5.23.
//
#pragma once
#define Helmet 0
#define Chest_plate 1
#define Gloves 2
#define Boots 3
#define Armoured_pants 4
#define Amulet 5

#define attack 1
#define abilities 2
#define invent 3
#ifndef UNTITLED8_CHARACTER_H
#define UNTITLED8_CHARACTER_H
enum Type {
    Type_NPC, Type_item, Type_monster, Default
};

#include <thread>


#include "Dialogue_manager.h"
#include <fstream>
#include <utility>
#include "Inventory.h"
#include "hp.h"

using namespace std;

class Character : public hp {
public:
    Character();

    Character(int Level, Attributes &Perks, int Damage, int Defence, int hp, int hpmax, string Name);

    ~Character();

    int get_level() const;

    virtual void add_Money(int Money);

    virtual int get_Money() const;

    virtual void Market(shared_ptr<Character> &person);

    int get_defence() const;

    virtual int get_def_damage() const;

    std::string get_name() const;

    virtual void Print(std::ostream &os);

    //Character doesn't know anything about Task, but it's used in Normal_NPC and in User
    virtual void Print_tasks(std::ostream &os) {
        os << "No tasks" << endl;

    }

    virtual bool addTask(bool Finished,
                         const string &Task_name,
                         const string &Task_description,
                         int award,
                         const vector<shared_ptr<Item>> &prizes,
                         Type type,
                         const shared_ptr<Character> &person_to_find,
                         const shared_ptr<Item> &item_to_find,
                         const shared_ptr<Character> &monster_to_find,
                         vector<Skill> &skills) {
        return true;
    }

    virtual bool operator==(const Character &other);

    void TakeDamage(int Damage) override;

    virtual bool Save_character_json(string Filename);

    virtual void Save_character_json_opened(nlohmann::json &json);

    virtual bool Load_character_json(std::string Filename);

    virtual void Load_character_json_opened(const nlohmann::json &json);

    virtual bool Put_in_left_hand(std::shared_ptr<Item> &item);

    virtual bool Put_in_Right_hand(std::shared_ptr<Item> &item);

    virtual bool Put_on_armour(std::shared_ptr<Item> &item);

    virtual bool Put_in_backpack(std::shared_ptr<Item> &item);

    virtual bool Increase_stat(const Skill &ski, int increase_mod);

    virtual bool Print_heal_items(std::ostream &os);

    virtual bool Use_heal_item(string Name, int &heal_effect);

    virtual bool Interaction(vector<shared_ptr<Character>> &monsters);

    virtual void Inventory_use();

    bool Full_Inventory(int num);

    int Free_places(int num);

    void Change_Damage(double modifikator);

    string class_name = "Character";
    bool Paralysed = false;
    Attributes perks;
protected:
    int money = 0;
    int level;
    int default_damage;
    int Right_hand_dmg = 0;
    int Left_hand_dmg = 0;
    int damage;
    int defence;
    Inventory inventory;
    std::string name;


};

long int_input_conversion();


#endif //UNTITLED8_CHARACTER_H
