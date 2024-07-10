//
// Created by fantomasm on 10.5.23.
//

#ifndef SEMESTRAL_WORK_ROOM_H
#define SEMESTRAL_WORK_ROOM_H

#include <utility>
#include <vector>
#include "Effect.h"
#include "User.h"
#include "Monster.h"
#include "Normal_NPC.h"
#include "Object.h"

class Room {

public:
    Room() : Room_name("Default message: Default room"),
             Room_description("Default message: Typical room with black cat and black-red tree") {}

    Room(string name, string description) : Room_name(std::move(name)), Room_description(std::move(description)) {}

    void addExit(const string &name);

    void addCharacter(const shared_ptr<Character> &character);

    void addObjects(const Object &obj);

    vector<shared_ptr<Character>> return_monsters();

    vector<shared_ptr<Character>> &return_characters();

    void Delete_monsters();

    vector<Object> &get_objects();

    vector<string> &get_exits();

    void read_from_json(const nlohmann::json &data);

    void to_json(nlohmann::json &json);

    void Print(std::ostream &os) const;

    string get_Room_name();

    bool Monsters = false;
private:
    std::string Room_name;
    std::string Room_description;
    std::vector<Object> Room_objects;

    std::vector<shared_ptr<Character>> Room_characters;
    std::vector<string> Room_exits;


};

#endif //SEMESTRAL_WORK_ROOM_H
