//
// Created by fantomasm on 23.5.23.
//
#define Speaking 1
#define Selling 2
#define Buying 3
#define Task_menu 4
#define Return_back 5

#include "Normal_NPC.h"

//Interaction with Normal Npc is divided into 5 sections
//Normal NPC is waiting for vector with user on first place
bool Normal_NPC::Interaction(vector<shared_ptr<Character>> &monsters) {
    if (monsters.size() != 2) {
        throw std::invalid_argument("Wrong size of vector");
    }
    clear();
    printw("1: Speak to %s\n", name.c_str());
    printw("2: Sell items\n");
    printw("3: Buy items\n");
    printw("4: Take tasks\n");
    printw("5: Return to previous menu\n");
    printw("Your input: ");
    refresh();

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long ch = int_input_conversion();


        if (ch > 5 || ch < 1) {
            printw("Wrong num :%ld, try again\n", ch);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            flushinp();
            refresh();

            continue;
        } else {
            switch (ch) {
                case Speaking:
                    Dialogue_interaction();
                    Interaction(monsters);
                    break;
                case Selling:
                    monsters[0]->Market(monsters[1]);
                    Interaction(monsters);
                    break;
                case Buying:
                    Market(monsters[0]);
                    Interaction(monsters);
                    break;
                case Task_menu:
                    Tasks(monsters[0]);
                    Interaction(monsters);


                    break;
                case Return_back:


                    break;


            }
            clear();
            refresh();
            break;
        }

    }
    return true;
}

//Market is almost the same as for user
void Normal_NPC::Market(shared_ptr<Character> &person) {
    clear();
    refresh();
    printw("List of selling items: \n");
    std::ostringstream os;
    inventory.Print(os, Backpack_cont);
    printw("%s", os.str().c_str());
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of item to buy it :");
    refresh();
    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        shared_ptr<Item> it = inventory.find_item(bufffer, 3);
        if (it != nullptr) {
            if (it->get_buy_value() > person->get_Money()) {
                printw("You dont have enough money to buy this\n");
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
            if (person->Full_Inventory(Backpack_cont)) {
                printw("Your backpack is full, you cant afford items without throwing out items\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();

                continue;
            }
            clear();
            refresh();
            person->Put_in_backpack(it);

            person->add_Money(-it->get_buy_value());

            printw("You successfully bought %s\n", it->Item_name.c_str());
            inventory.Delete_Item(it, Backpack_cont);

            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            clear();
            refresh();
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            return;

        } else {

            printw("Wrong input :%s , try again", bufffer);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();
            flushinp();
        }

    }

}

void Normal_NPC::Print_tasks(std::ostream &os) {
    for (const auto &task: tasks) {
        task.Print(os);
    }

}

void Normal_NPC::Tasks(shared_ptr<Character> &person) {
    clear();
    refresh();
    printw("Tasks: \n");
    std::ostringstream os;
    Print_tasks(os);
    printw("%s", os.str().c_str());
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of task to take it :");
    refresh();
    char bufffer[256];


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        bool found = false;
        Task it;
        size_t pos = 0;
        for (const auto &task: tasks) {
            if (task.Task_name == bufffer) {
                it = task;
                found = true;
                break;
            }
            pos++;
        }
        //If task is found, we give his parameters to user and delete it from ourselves
        if (found) {

            if (!person->addTask(it.Finished, it.Task_name, it.Task_description, it.award, it.prizes, it.type,
                                 it.person_to_find, it.item_to_find, it.monster_to_find,
                                 it.skills_for_task)) {
                printw("You dont have enough skills for this task\n");
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
            clear();
            printw("Adding task \"%s\" to task's list\n", it.Task_name.c_str());
            refresh();
            tasks.erase(tasks.begin() + static_cast<int>(pos));
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            clear();
            refresh();
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            return;

        } else {

            printw("Wrong input :%s , try again", bufffer);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();
        }

    }
}

bool Normal_NPC::Save_character_json(string Filename) {
    nlohmann::json json;


    Filename += "Normal_NPC";

    Filename += ".json";

    ofstream new_file;
    new_file.open(Filename, std::ios::trunc);
    if (!new_file.is_open()) {

        throw std::runtime_error("Failed to open file: " + Filename);

    } else {
        Save_character_json_opened(json);
        ///save dialogs here

        new_file << json.dump(4);
        new_file.close();
        return true;
    }
}

void Normal_NPC::Save_character_json_opened(nlohmann::json &json) {
    Character::Save_character_json_opened(json);
    json["Description"] = Description;
    json["tasks"] = nullptr;
    for (const auto &task: tasks) {
        json["tasks"].push_back(task.to_json());
    }
    manager->to_json(json);
}

bool Normal_NPC::Load_character_json(std::string Filename) {


    Filename += "Normal_NPC";

    Filename += ".json";

    ifstream new_file;
    new_file.open(Filename, std::ios::in);
    if (!new_file.is_open()) {


        throw std::runtime_error("Failed to open file: " + Filename);

    } else {

        nlohmann::json jsonData;
        new_file >> jsonData;
        Load_character_json_opened(jsonData);

        return true;
    }
}

void Normal_NPC::Load_character_json_opened(const nlohmann::json &json) {
    Character::Load_character_json_opened(json);

    Description = json["Description"];

    if (!json["tasks"].is_null() && !json["tasks"].empty()) {
        for (const auto &task: json["tasks"]) {
            Task new_task;
            new_task.from_json(task);
            tasks.push_back(new_task);
        }
    }

    manager->from_json(json);

}

void Normal_NPC::Dialogue_interaction() {
    clear();
    refresh();
    manager->start_Dialogue();
    manager->Restart_dialogue();
}

void Normal_NPC::Print(std::ostream &os) {
    os << name << std::endl;
    os << Description << std::endl;
}