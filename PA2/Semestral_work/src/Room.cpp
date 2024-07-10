//
// Created by fantomasm on 10.5.23.
//

#include "Room.h"

void Room::read_from_json(const nlohmann::json &data) {

    Room_name = data["Room_name"];
    Room_description = data["Room_description"];

    if (!data["Room_objects"].is_null() && !data["Room_objects"].empty()) {
        for (const auto &obj: data["Room_objects"]) {
            Object object;
            object.from_json(obj);
            addObjects(object);

        }
    }

    if (!data["Room_exits"].is_null() && !data["Room_exits"].empty()) {
        for (const auto &exits: data["Room_exits"]) {
            addExit(exits);
        }
    }

    if (!data["Room_characters"].is_null() && !data["Room_characters"].empty()) {

        if (!data["Room_characters"][0]["Monster"].is_null() && !data["Room_characters"][0]["Monster"].empty()) {
            Monsters = true;
            for (const auto &monsters: data["Room_characters"][0]["Monster"]) {

                refresh();

                Monster mon;
                mon.Load_character_json_opened(monsters);
                addCharacter(make_shared<Monster>(mon));

            }
        }

        if (!data["Room_characters"][1]["Normal_NPC"].is_null() && !data["Room_characters"][1]["Normal_NPC"].empty()) {

            for (const auto &normal_npc: data["Room_characters"][1]["Normal_NPC"]) {

                Normal_NPC npc;
                npc.Load_character_json_opened(normal_npc);
                addCharacter(make_shared<Normal_NPC>(npc));
            }
        }

    }

}

void Room::addExit(const std::string &name) {

    Room_exits.push_back(name);

}

void Room::addCharacter(const shared_ptr<Character> &character) {

    Room_characters.push_back(character);

}

void Room::addObjects(const Object &obj) {
    Room_objects.push_back(obj);

}

vector<std::shared_ptr<Character>> Room::return_monsters() {

    vector<shared_ptr<Character>> monsters;
    for (const auto &characters: Room_characters) {
        if (characters->class_name == "Monster") {
            monsters.push_back(characters);
        }
    }
    return monsters;

}

vector<std::shared_ptr<Character>> &Room::return_characters() {


    return Room_characters;

}

//Deleting all monsters, used after battle
void Room::Delete_monsters() {

    Room_characters.erase(
            std::remove_if(Room_characters.begin(), Room_characters.end(), [](const std::shared_ptr<Character> &ptr) {
                return ptr->class_name == "Monster";
            }), Room_characters.end());
    Monsters = false;

}

vector<Object> &Room::get_objects() {

    return Room_objects;

}

vector<std::string> &Room::get_exits() {

    return Room_exits;

}

void Room::Print(std::ostream &os) const {

    os << Room_name << std::endl << Room_description << std::endl << std::endl;
    os << "Objects in area: \n";
    for (const auto &obj: Room_objects) {
        obj.Print(os);
    }
    os << std::endl;
    os << "Characters: \n";
    for (const auto &character: Room_characters) {
        if (character->class_name == "Normal_NPC") {
            character->Print(os);
        }
    }
    os << std::endl;
    os << "Room exits: \n";
    for (const auto &exit: Room_exits) {
        os << exit << endl;
    }
    os << std::endl;


}

std::string Room::get_Room_name() {

    return Room_name;

}

void Room::to_json(nlohmann::json &json) {
    json["Room_name"] = Room_name;
    json["Room_description"] = Room_description;
    json["Room_objects"] = nullptr;
    for (auto &room_object: Room_objects) {
        nlohmann::json obj;
        room_object.to_json(obj);
        json["Room_objects"].push_back(obj);
    }
    json["Room_exits"] = nullptr;
    for (const auto &exit: Room_exits) {
        json["Room_exits"].push_back(exit);
    }
    json["Room_characters"] = nullptr;
    json["Room_characters"][0]["Monster"] = nullptr;
    json["Room_characters"][1]["Normal_NPC"] = nullptr;
    for (const auto &mon: Room_characters) {
        if (mon->class_name == "Monster") {
            nlohmann::json mon_json;
            mon->Save_character_json_opened(mon_json);
            json["Room_characters"][0]["Monster"].push_back(mon_json);
        }
        if (mon->class_name == "Normal_NPC") {
            nlohmann::json mon_json;
            mon->Save_character_json_opened(mon_json);
            json["Room_characters"][1]["Normal_NPC"].push_back(mon_json);
        }
    }
}