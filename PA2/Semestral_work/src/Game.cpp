//
// Created by fantomasm on 3.5.23.
//
#include "Game.h"
#include <iostream>

#define Objects_interaction 1
#define Character_interaction 2
#define Exits 3
#define User_inventory 4
#define Tasks_list 5

#define Exit_game 6
#define Save_game 7
using namespace std;


bool Game::Init() {
    initscr();
    //Initializing screen and reading basic information

    //Reading basic perks
    try {
        basic_skills.read_skills_from_json_file("examples/Configuration/attributtes.json");
    }
    catch (const std::runtime_error &ex) {
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }

    //Reading basic archetypes for future choosing
    try {
        Load_archetypes("examples/Configuration/archetypes.json");
    }
    catch (const std::runtime_error &ex) {
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }
    //Reading game areas
    try {
        Load_Rooms("examples/Configuration/Rooms/rooms");
    }
    catch (const std::runtime_error &ex) {
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));;
        return false;
    }

    //Reading saves
    try {
        Load_saves();
    }
    catch (const std::runtime_error &ex) {
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return false;
    }

    return true;

};


Game::Game() : Game_is_running(true), choice(0) {}

Game::~Game() = default;

void Game::Finish_game() {
    Game_is_running = false;
}

bool Game::Battle(vector<shared_ptr<Character>> monsters) {
    clear();
    refresh();

    if (monsters.size() > 1) {
        printw("You were attacked by monsters \n");
    } else {
        printw("You were attacked by monster  \n");
    }

    //Inserting user pointer and default constructor to vector of monsters
    //Because active effects trait second element in monsters as user and next elements are enemies
    monsters.insert(monsters.begin(), user_ptr);
    monsters.insert(monsters.begin(), make_shared<Character>());
    refresh();
    //Passive effects trait first element as user, that's why we create another vector with user on a first place
    vector<shared_ptr<Character>> user;
    user.push_back(user_ptr);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    clear();
    refresh();
    //Getting reward from monsters on the start, because in case of loose user will exit to main menu
    int award = 0;
    for (size_t i = 2; i < monsters.size(); i++) {
        award += monsters[i]->get_level() * 10;
    }
    user_ptr->add_Money(award);

    //Main battle loop
    while (true) {
        //Polymorphic call of Interaction method
        //In case of user it prints menu and variants , what to do with monsters, in case of monsters they just deal random damage and also can heal themselves, if they have healing items
        for (size_t i = 1; i < monsters.size(); i++) {
            monsters[i]->Interaction(monsters);
        }

        clear();
        refresh();
        //Hp of user cant get under 0, so if its 0, user is dead
        if (user_ptr->get_HP() == 0) {
            printw("You died...\n");
            refresh();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            clear();
            refresh();
            return false;

        }
        //If in vector are only user and default character, then user wins and heals to maxHP
        //Also he is getting reward and exp, exp is gotten for money
        if (monsters.size() == 2) {
            printw("You won this battle\n");
            user_ptr->Heal(user_ptr->get_MaxHP());
            //deactivating berserk effect, if so
            Passive_effects_user(user);
            refresh();
            std::this_thread::sleep_for(std::chrono::seconds(2));
            return true;

        }

        //Activating passive effects : Regeneration , berserk
        //Regeneration is activated after checking if user is dead to avoid situations when user revive from 0 hp
        //berserk is increasing damage when hp is low
        Passive_effects_user(user);


        printw("You have %d HP left\n", user[0]->get_HP());
        refresh();


    }
}

void Game::Passive_effects_user(vector<shared_ptr<Character>> &user) {
    for (const auto &eff: current_user.archetype.effects) {
        eff->apply_effect(user);

    }
}

void Game::Using_Inventory() {
    user_ptr->Inventory_use();
}

//Loading game areas
void Game::Load_area_play(const string &name_next_room) {
    auto it = rooms.find(name_next_room);
    if (it != rooms.end()) {
        Room &room = it->second;
        current_room = room.get_Room_name();
        prev_room = current_room;
        //After moving to new area, program checks , if there are monsters, if so, user will be forced to fight with them
        if (room.Monsters) {
            clear();
            refresh();
            //In case of successful fight, monsters will be deleted from room
            if (Battle(room.return_monsters())) {

                room.Delete_monsters();
            }
                //In case of failure prev room is set to different name from current room to avoid next loop
                // and inside game is stopped, user will be thrown up to main menu
            else {
                prev_room = "prev_rom";
                Inside_game_is_running = false;
            }


        }
        //main loop for working with area
        while (current_room == prev_room) {

            Area_menu(room);
        }


    }
        //If room cant be found, we forced to throw an exception, game cant be continued, because files are missing
    else {

        throw std::runtime_error("Cant find information about: " + name_next_room);
    }
}

void Game::Area_menu(Room &cur_room) {
    clear();
    //Main area menu
    //It prints short describe of area: objects,characters,exits and so
    std::ostringstream os;
    cur_room.Print(os);
    printw("%s", os.str().c_str());
    refresh();
    printw("1: Interaction with objects\n");
    printw("2: Interaction with characters\n");
    printw("3: Move to another area\n");
    printw("4: Interaction with inventory\n");
    printw("5: See your tasks\n");
    printw("6: Return to main menu *without save*\n");
    printw("7: Save game\n");
    printw("Your input: ");
    refresh();
    //basic value for reading user's input

    flushinp();


    while (true) {
        //Getting x and y values to know where to return
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long ch = int_input_conversion();

        //In case of wrong input program will print error message on next line and after second it will disappear
        if (ch > 7 || ch < 1) {
            printw("Wrong num :%ld, try again\n", ch);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();
            flushinp();

            continue;
        } else {
            switch (ch) {
                case Objects_interaction:
                    Object_interaction(cur_room.get_objects());
                    break;
                case Character_interaction:
                    Characters_interaction(cur_room.return_characters());
                    break;
                case Exits:
                    Exit_interaction(cur_room.get_exits());
                    break;
                case User_inventory:
                    Using_Inventory();

                    break;
                    //In case of exit game we stop inside loop and prev_room is set to different name to exit from loop in load_area_play
                case Exit_game:
                    Inside_game_is_running = false;
                    prev_room = "prev_room";
                    break;
                case Save_game:
                    //Saving game can be unsuccessful , but game will continue after indicating that save wasn't successful
                    try {
                        Save();
                    }
                    catch (const std::runtime_error &ex) {
                        printw("Error: %s\n", ex.what());
                        printw("Unsuccessful save\n");
                        refresh();
                        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                        clear();
                        refresh();
                        break;

                    }
                    printw("\nSuccessful save\n");
                    refresh();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    clear();
                    refresh();
                    break;
                case Tasks_list:
                    Tasks_print();

                    break;


            }
            clear();
            refresh();
            break;
        }

    }
}

void Game::Tasks_print() {
    //Printing user's tasks
    clear();
    printw("Your tasks  : \n");
    std::ostringstream os1;
    user_ptr->Print_tasks(os1);
    printw("%s", os1.str().c_str());
    printw("Print \"Back\" for turning back to menu\n");
    printw("Your input: ");
    refresh();
    char buffer[256];

    while (true) {
        //interaction with input is the same as before, getting info about x, y position to delete wrong input and error message
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(buffer, sizeof(buffer) - 1);


        if (string(buffer) == "Back") {
            clear();
            refresh();
            break;
        } else {
            printw("Wrong input :%s , try again", buffer);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            flushinp();
            refresh();
        }

    }
}

void Game::Exit_interaction(vector<std::string> &exits) {
    clear();

    size_t i = 1;
    //Printing exits from current room
    //Exits are just strings and also a key in a hashmap of rooms
    for (; i <= exits.size(); i++) {
        printw("%zu: %s\n", i, exits[i - 1].c_str());
    }
    //Number right after vector's indexes is sign for exit
    printw("%zu: Back to previous menu\n", i);
    refresh();


    while (true) {

        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long number = int_input_conversion();
        number--;
        //Wrong input can be in case of input outside of exit's vector
        if (number > static_cast<long int>(exits.size()) || number < 0) {
            printw(" wrong num: %ld , try again", number + 1);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();
            flushinp();

            continue;
        }
        //If input is equal to size of vector, it indicates exit_message from this menu
        if (number == static_cast<long int>(exits.size())) {
            clear();
            refresh();
            break;
        } else {
            //changing current room to new value
            current_room = exits[number];

            clear();
            refresh();

            break;
        }

    }
}

void Game::Characters_interaction(vector<shared_ptr<Character>> &characters) {
    clear();
    std::ostringstream os;
    size_t pos = 1;
    for (const auto &obj: characters) {
        os << pos << " : ";
        obj->Print(os);
        pos++;
    }
    clear();
    printw("%s", os.str().c_str());
    refresh();
    printw("%zu: Back to menu\n", pos);
    printw("Your input: ");
    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long character = int_input_conversion();
        //changing index to right one, because indexes for user starting from 1, but actually from 0
        character--;

        if (character > static_cast<long int>(characters.size()) || character < 0) {
            printw(" wrong num: %ld , try again", character + 1);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();
            flushinp();

            continue;
        }
        if (character == static_cast<long int>(characters.size())) {
            clear();
            refresh();
            break;
        } else {
            //Interaction with Normal_NPC, normal_npc is waiting for user on first place of vector of shared_ptr<Character>
            std::vector<shared_ptr<Character>> user;
            user.push_back(user_ptr);
            user.push_back(characters[character]);
            characters[character]->Interaction(user);

            clear();
            refresh();
            //recursive call to same function to avoid returning to few methods back
            Characters_interaction(characters);
            break;
        }

    }

}

bool Game::Create_new_character() {
    //Loading basic archetypes and rooms again to restore basic data
    archetypes.clear();
    try {
        Load_archetypes("examples/Configuration/archetypes.json");
    }
    catch (const std::runtime_error &ex) {
        clear();
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return false;
    }
    rooms.clear();
    try {
        Load_Rooms("examples/Configuration/Rooms/rooms");
    }
    catch (const std::runtime_error &ex) {
        clear();
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return false;
    }
    clear();
    printw("Character's name: ");
    refresh();
    int xname = getcurx(stdscr);
    int yname = getcury(stdscr);
    char name[256];



    //Getting username with checking, if save of such username is already exists
    while (true) {
        bool same = false;
        flushinp();
        getnstr(name, sizeof(name) - 1);
        if (!string(name).empty()) {
            for (const std::string &Name: Loads) {
                if (string(name) == Name) {
                    printw("User with same name already exists, please choose other name\n");
                    refresh();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    move(yname + 1, 0);
                    clrtoeol();
                    move(yname, xname);
                    clrtoeol();
                    same = true;
                    break;


                }
            }
            //Also username cant be same as name of system files
            if (string(name) == "." || string(name) == "..") {
                printw("Cant use such name\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                move(yname + 1, 0);
                clrtoeol();
                move(yname, xname);
                clrtoeol();
                continue;
            }
            if (!same) {
                break;
            }


        }

    }
    Attributes new_skills(basic_skills);
    clear();
    refresh();
    printw("Your name is %s\n", name);
    printw("Choose your skills\n");
    printw("You have 5 points for improving skills\n");

    //Printing menu with skills
    new_skills.Print_to_screen();
    printw("%zu: Skip points distributing\n", new_skills.skills_count() + 1);
    printw("Your input : ");

    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long character = int_input_conversion();
        character--;

        if (character > static_cast<long int>(new_skills.skills_count()) || character < 0) {
            printw(" wrong num: %ld , try again", character);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            flushinp();
            refresh();

            continue;
        }
        if (character == static_cast<long int>(new_skills.skills_count())) {
            clear();
            refresh();
            break;
        } else {
            //if this method returns false, it indicates, that user don't have enough points for upgrading this skill
            if (!new_skills.use_free_points(static_cast<int>(character))) {
                printw(" You dont have enough points for this skill");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                flushinp();
                refresh();

                continue;
            }
            clear();
            //Printing skills again to show user , where skills level changes
            new_skills.Print_to_screen();
            printw("%zu: Skip points distributing\n", new_skills.skills_count() + 1);
            printw("Your input : ");

            refresh();
            flushinp();
            continue;

        }

    }


    clear();
    refresh();
    User new_user(1, new_skills, 1, 1, 100, 100, name);
    //Loading basic file with user, user can defined damage, level, hp, basic items and so on
    try{
    new_user.first_load("examples/Configuration/Default/");
	}
	catch (const std::runtime_error &ex) {
        clear();
        printw("Error: %s\n", ex.what());
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return false;
    }
	




    //Choosing archetype of user
    printw("Now choose your archetype\n");
    std::ostringstream os;

    for (const auto &archetype: archetypes) {
        archetype->Print(os);

    }
    char buffer[256];
    printw("%s\n", os.str().c_str());
    printw("Print the name of class to choose it\n");
    printw("Your input : ");
    refresh();
    bool found = false;
    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(buffer, sizeof(buffer) - 1);
        //Finding archetype by name
        for (const auto &archetype: archetypes) {
            if (archetype->class_name == string(buffer)) {
                new_user.archetype = *archetype;
                found = true;

            }
        }
        if (found) {
            break;
        } else {
            printw(" wrong name: %s , try again", buffer);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            flushinp();
            refresh();

            continue;
        }

    }
    //Making shared ptr for user
    std::shared_ptr<Character> user = make_shared<User>(std::ref(new_user));
    clear();

    refresh();
    user_ptr = user;
    //Printing main tasks in game, if so
    std::ostringstream os1;
    user_ptr->Print_tasks(os1);
    //Checking if there is any text in os1
    if (os1.good()) {
        printw("Your main tasks in game : \n");

        printw("%s", os1.str().c_str());
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    }
    clear();
    refresh();

    return true;


}

bool Game::Load_saves() {
    std::string folderPath = "examples/Saves/";

    DIR *dir;
    struct dirent *entry;
    struct stat fileStat{};

    //open directory with saves
    dir = opendir(folderPath.c_str());
    if (dir == nullptr) {
        throw std::runtime_error("Failed to open file: " + folderPath);
        return false;

    }


    //Going through all files in saves and adding their names(username) to vector of loads
    while ((entry = readdir(dir)) != nullptr) {
        std::string name = entry->d_name;
        std::string fullPath = folderPath;
        fullPath += "/";
        fullPath += name;

        if (stat(fullPath.c_str(), &fileStat) != -1) {

            if (S_ISDIR(fileStat.st_mode)) {
                if (name != "." && name != "..") {
                    Loads.push_back(name);
                }

            }
        }
    }


    closedir(dir);
    return true;
}

bool Game::Load_user() {
    //Load new saves to loads
    Loads.clear();
    Load_saves();


    size_t pos = 1;
    printw("List of profiles to load: \n");
    for (const auto &load: Loads) {
        printw("%zu: %s\n", pos, load.c_str());
        pos++;
    }
    printw("%zu: For exit from menu\n", pos);
    printw("Your input: ");
    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long character = int_input_conversion();
        character--;
        //Same checks if input isn't out of vector, also if character is 0,(unsuccessful conversion), it also will indicate as failure
        if (character > static_cast<long int>(Loads.size()) || character < 0) {
            printw(" wrong num: %ld , try again", character + 1);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            flushinp();
            refresh();

            continue;
        }
        if (character == static_cast<long int>(Loads.size())) {
            clear();
            refresh();

            return false;
        } else {
            clear();
            std::string Filename = "examples/Saves/";
            Filename += Loads[character];
            Filename += "/";
            User to_load;
            to_load.Load_character_json(Filename);
            //Checking if skills in user are same as basic skills
            //If no, it indicates that perks profile or user profile is wrong/taken from another asset of game
            if (!basic_skills.Has_such_skills(to_load.perks)) {
                throw std::runtime_error("No such skills in user profile, wrong file");
            }

            Filename += "rooms";
            //Loading areas from user's file
            Load_Rooms(Filename);
            bool found = false;
            //Looking for user's archetype, in user's load it loads only name of archetype, his effects are stored in game
            for (auto &archetype: archetypes) {
                if (to_load.archetype.class_name == archetype->class_name) {
                    to_load.archetype = *archetype;
                    std::ostringstream os1;
                    to_load.archetype.Print(os1);
                    found = true;
                    break;
                }
            }
            //Same as with perks, indicates that some file is taken from wrong asset
            if (!found) {
                throw std::runtime_error("Wrong data, archetypes dont have such archetype");
            }

            std::shared_ptr<Character> user = std::make_shared<User>(to_load);
            user_ptr = user;

            refresh();
            flushinp();
            return true;
            break;

        }

    }

}

void Game::Main_menu() {
    prev_room = current_room;

    printw("1: Start New Game\n");
    printw("2: Load Game\n");
    printw("3: Quit Game\n");
    printw(" Choice : ");
    int x = getcurx(stdscr);
    int y = getcury(stdscr);
    refresh();


    flushinp();
    while (true) {

        long character = int_input_conversion();
        switch (character) {
            case 1:
                //if creating of character wasn't successful, it indicates that some files can't be loaded, that's why game cant be played
                if (!Create_new_character()) {
                    prev_room = "prev_room";
                    Game_is_running = false;
                } else {
                    Inside_game_is_running = true;
                    current_room = start_room;
                    prev_room = start_room;
                }
                clear();
                refresh();
                break;
                break;
            case 2:
                try {
                    clear();
                    refresh();
                    //load user is returning true in case of successful load
                    if (Load_user()) {
                        Inside_game_is_running = true;
                        current_room = start_room;
                        prev_room = current_room;
                        clear();
                        printw("\nSuccessful load\n");
                        refresh();
                        //false is returned in case of returning back from method
                    } else {
                        clear();
                        refresh();
                        break;
                    }
                }
                    //in case of unsuccessful load exception is thrown and game is stopped
                catch (const std::runtime_error &ex) {
                    clear();
                    printw("Error : %s\n", ex.what());
                    refresh();
                    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                    Finish_game();
                }
                refresh();

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                clear();
                refresh();
                break;
                break;
            case 3:
                Finish_game();

                clear();
                refresh();

                break;
            default:
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                flushinp();
                refresh();

                continue;
                break;
        }
        break;


        clear();
        refresh();

    }


}

//Main game loop, in outer loop there are interactions with main menu and inside menu is interacting with area's(room's)
void Game::Run() {
    //if init was unsuccessful, game is stopped
    if (!Init()) {
        Game_is_running = false;
    }
    while (Game_is_running) {

        Main_menu();

        while (Inside_game_is_running) {
            try {
                Load_area_play(current_room);
            }
            catch (const std::runtime_error &ex) {

                printw("Error: %s\n", ex.what());
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                Inside_game_is_running = false;
                Game_is_running = false;
            }

        }
    }
    endwin();

}

bool fileExists(const std::string &filename) {
    std::ifstream file(filename);
    return file.good();
}

//Saving character
bool Game::Save() {
    std::string name = "examples/Saves/";
    name += user_ptr->get_name();
    //if file is already exist, then we just rewrite data
    if (fileExists(name)) {
        name += '/';
        user_ptr->Save_character_json(name);

        Save_Rooms(name);
        return true;
    }
    //in other case we should create new folder and files in it
    if (mkdir(name.c_str(), 0777) == 0) {
        name += '/';
        user_ptr->Save_character_json(name);

        Save_Rooms(name);
        return true;
    } else {
        throw std::runtime_error("Failed to create folder: " + name);
        return false;
    }
}

bool Game::Save_Rooms(std::string Filename) {
    Filename += "rooms";

    Filename += ".json";

    nlohmann::json json;



    //Saving rooms in rooms.json file
    ofstream new_file;
    new_file.open(Filename, std::ios::trunc);
    if (!new_file.is_open()) {

        throw std::runtime_error("Failed to open file: " + Filename);
        return false;
    } else {
        json["Start_room"] = current_room;
        //inserting nullptr to rooms array to avoid problems with no rooms array
        json["rooms"] = nullptr;
        for (auto &room: rooms) {
            nlohmann::json json1;
            room.second.to_json(json1);
            json["rooms"].push_back(json1);

        }

        new_file << json.dump(4);
        new_file.close();
        return true;
    }
}

//Loading archetypes
bool Game::Load_archetypes(const string &filename) {
    ifstream new_file;
    new_file.open(filename, std::ios::in);
    if (!new_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);

        return false;
    } else {
        nlohmann::json jsonData;
        new_file >> jsonData;
        if (!jsonData["archetypes"].is_null()) {
            for (const auto &type: jsonData["archetypes"]) {
                std::string className = type["class_name"];


                Archetype new_archetype(className);
                if (new_archetype.from_json(type)) {
                    archetypes.push_back(make_shared<Archetype>(new_archetype));
                } else {
                    throw std::runtime_error("Cant find data about archetype's effects");

                    return false;
                }


            }
        }
    }
    return true;
}

//Loading rooms
bool Game::Load_Rooms(const string &Filename) {
    string filename_rooms;
    filename_rooms += Filename;

    filename_rooms += ".json";

    ifstream new_file;
    new_file.open(filename_rooms, std::ios::in);
    if (!new_file.is_open()) {


        throw std::runtime_error("Failed to open file: " + filename_rooms);
        return false;
    } else {

        nlohmann::json jsonData;
        new_file >> jsonData;

        start_room = jsonData["Start_room"];
        if (!jsonData["rooms"].is_null()) {
            for (const auto &room: jsonData["rooms"]) {
                Room to_Load;
                to_Load.read_from_json(room);

                rooms[to_Load.get_Room_name()] = to_Load;

            }
        }
            //If there are no rooms(areas), game cant be played
        else {
            throw std::runtime_error("No data in file: " + filename_rooms);
        }
        return true;
    }
}

//interaction with objects
void Game::Object_interaction(vector<Object> &objects) {
    std::ostringstream os;
    size_t pos = 1;
    for (const auto &obj: objects) {
        os << pos << " : ";
        obj.Print(os);
        pos++;
    }
    clear();
    printw("%s", os.str().c_str());
    refresh();
    printw("%zu: Back to menu\n", pos);
    printw("Your input: ");
    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long character = int_input_conversion();
        character--;
        if (character > static_cast<long int>(objects.size()) || character < 0) {
            printw(" wrong num: %ld , try again", character + 1);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();

            continue;
        }
        if (character == static_cast<long int>(objects.size())) {
            clear();
            refresh();
            break;
        } else {
            objects[character].Interaction(user_ptr);
            if (objects[character].Is_destroyed()) {
                objects.erase(objects.begin() + static_cast<int>(character));
            }
            clear();
            refresh();
            break;
        }

    }
}
