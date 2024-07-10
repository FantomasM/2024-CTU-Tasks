//
// Created by fantomasm on 3.5.23.
//

#ifndef UNTITLED8_GAME_H
#define UNTITLED8_GAME_H

#include "Room.h"

#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <chrono>
#include <thread>


class Game {
public:
    bool Game_is_running;

    bool Init();

    void Main_menu();

    void Finish_game();

    bool Create_new_character();

    bool Load_archetypes(const string &filename);

    bool Load_Rooms(const string &Filename);

    bool Save_Rooms(string Filename);

    bool Save();

    bool Load_saves();

    bool Load_user();

    bool Battle(vector<shared_ptr<Character>> monsters);

    void Passive_effects_user(vector<shared_ptr<Character>> &user);

    void Using_Inventory();

    void Area_menu(Room &cur_room);

    void Load_area_play(const string &name_next_room);

    void Object_interaction(vector<Object> &objects);

    void Characters_interaction(vector<shared_ptr<Character>> &characters);

    void Exit_interaction(vector<std::string> &exits);

    void Tasks_print();

    void Run();

    Game();

    ~Game();

private:
    int choice;
    std::string start_room = "Start";
    std::string current_room = "Start";
    std::string prev_room = "Start";
    bool Inside_game_is_running = false;
    Attributes basic_skills;

    User current_user;
    std::shared_ptr<Character> user_ptr;
    unordered_map<std::string, Room> rooms; //starting room always have name "Start"
    std::vector<std::shared_ptr<Archetype>> archetypes; // list of archetypes to be chosen
    std::vector<std::string> Loads; // vector stores filename and archetype name
protected:

};

#endif //UNTITLED8_GAME_H
