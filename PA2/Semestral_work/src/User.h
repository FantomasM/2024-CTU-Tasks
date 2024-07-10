//
// Created by fantomasm on 9.5.23.
//

#ifndef SEMESTRAL_WORK_USER_H
#define SEMESTRAL_WORK_USER_H

#include "Task.h"
#include "Archetype.h"

class User : public Character {
public:
    User() : Character(), exp(0), exp_next(1000) {}

    User(int Level, Attributes &Perks, int Damage, int Defence, int hp, int hpmax, string Name) : Character(Level,
                                                                                                            Perks,
                                                                                                            Damage,
                                                                                                            Defence, hp,
                                                                                                            hpmax,
                                                                                                            std::move(
                                                                                                                    Name)),
                                                                                                  perks(Perks),
                                                                                                  exp(0),
                                                                                                  exp_next(200) {}

    User(User &other) : Character(other.level, other.perks, other.damage, other.defence, other.HP, other.MaxHP,
                                  other.name), exp(other.exp), exp_next(other.exp_next) {
        inventory = other.inventory;
        money = other.money;
        tasks = other.tasks;
        perks = other.perks;
        archetype = other.archetype;

    }

    bool Save_character_json(string Filename) override;

    void Save_character_json_opened(nlohmann::json &json) override;

    bool Load_character_json(std::string Filename) override;

    void Load_character_json_opened(const nlohmann::json &jsonData) override;

    void first_load(std::string Filename);

    void Print_tasks(std::ostream &os) override;

    void add_Money(int Money) override;

    bool Put_in_backpack(std::shared_ptr<Item> &item) override;

    void Print(std::ostream &os) override;


    bool Increase_stat(const Skill &ski, int increase_mod) override;

    bool addTask(bool Finished,
                 const string &Task_name,
                 const string &Task_description,
                 int award,
                 const vector<shared_ptr<Item>> &prizes,
                 Type type,
                 const shared_ptr<Character> &person_to_find,
                 const shared_ptr<Item> &item_to_find,
                 const shared_ptr<Character> &monster_to_find, vector<Skill> &skills) override;


    bool Interaction(vector<shared_ptr<Character>> &monsters) override;

    void Inventory_use() override;

    Archetype archetype;
    Attributes perks;
private:
    void Attack(vector<shared_ptr<Character>> &monsters);

    void User_Using_abilities(vector<shared_ptr<Character>> &monsters);

    void Using_heal_items(vector<shared_ptr<Character>> &monsters);

    void Weapon_On();

    void Weapon_Off();

    void Armour_On();

    void Armour_Off();

    void Delete_Item();

    void Upgrade_level();

    bool Item_saver_use();

protected:


    int exp = 0;
    int exp_next = 100;
    vector<Task> tasks;

};

#endif //SEMESTRAL_WORK_USER_H
