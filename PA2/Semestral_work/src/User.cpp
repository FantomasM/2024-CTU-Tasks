//
// Created by fantomasm on 9.5.23.
//
#define Weapon_on 1
#define Weapon_off 2
#define Armour_on 3
#define Armour_off 4
#define Delete_item 5
#define Item_saver_usement 6
#define Previous_menu 7

#include "User.h"


void User::Save_character_json_opened(nlohmann::json &json) {

    Character::Save_character_json_opened(json);

    json["perks"] = perks.toJson();
    json["tasks"] = nullptr;
    for (const auto &task: tasks) {
        json["tasks"].push_back(task.to_json());
    }

    json["Archetype"] = archetype.class_name;
    json["exp"] = exp;
    json["exp_next"] = exp_next;
    json["money"] = money;


}

//First load for user, name and perks are already in User, other components are got from default file
void User::first_load(std::string Filename) {


    Filename += "User";

    Filename += ".json";

    ifstream new_file;
    new_file.open(Filename, ios::out | ios::app);
    if (!new_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + Filename);


    } else {

        nlohmann::json jsonData;
        new_file >> jsonData;
        level = jsonData["level"];
        damage = jsonData["damage"];
        default_damage = damage;
        defence = jsonData["defence"];
        HP = jsonData["HP"];
        MaxHP = jsonData["HPmax"];
        exp = jsonData["exp"];
        exp_next = jsonData["exp_next"];
        money = jsonData["money"];
        size_t i = 0;
        for (const auto &inv: jsonData["inventory"]) {
            std::string className1 = inv["Class name"];

            if (!inv["Items"].is_null()) {
                for (const auto &jsonItem: inv["Items"]) {
                    std::string className = jsonItem["Class_name"];
                    ItemPtr obj = ItemFactory::create(className);
                    obj->from_json(jsonItem);
                    inventory.Inv[i]->Add_Item(obj);
                }
            }
            i++;
        }
        for (const auto &task: jsonData["Tasks"]) {
            Task new_task;
            new_task.from_json(task);
            tasks.push_back(new_task);
        }


    }
}

bool User::Save_character_json(string Filename) {


    nlohmann::json json;


    Filename += "User";

    Filename += ".json";

    ofstream new_file;
    new_file.open(Filename, std::ios::trunc);
    if (!new_file.is_open()) {

        throw std::runtime_error("Failed to open file: " + Filename);

    } else {
        Save_character_json_opened(json);

        new_file << json.dump(4);
        new_file.close();
        return true;
    }
}

void User::Load_character_json_opened(const nlohmann::json &jsonData) {
    Character::Load_character_json_opened(jsonData);


    perks.fromJson(jsonData["perks"]);


    if (!jsonData["tasks"].is_null() && !jsonData["tasks"].empty()) {
        for (const auto &task: jsonData["tasks"]) {
            Task new_task;
            new_task.from_json(task);
            tasks.push_back(new_task);
        }
    }
    money = jsonData["money"];
    exp = jsonData["exp"];
    exp_next = jsonData["exp_next"];
    archetype.class_name = jsonData["Archetype"];

}

bool User::Load_character_json(std::string Filename) {


    Filename += "User";

    Filename += ".json";

    ifstream new_file;
    new_file.open(Filename, ios::out | ios::app);
    if (!new_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + Filename);

    } else {

        nlohmann::json jsonData;
        new_file >> jsonData;
        Load_character_json_opened(jsonData);


        return true;
    }

}


bool User::Increase_stat(const Skill &ski, int increase_mod) {
    return perks.activate_bonus_int(ski, increase_mod);
}

//Deleted completed tasks from vector of tasks
void Delete_completed(std::vector<Task> &tasks) {

    tasks.erase(std::remove_if(tasks.begin(), tasks.end(), [](const Task &ptr) {
        return ptr.Finished;
    }), tasks.end());

}

//Putting items in backpack with control, if item is not an item from task
bool User::Put_in_backpack(std::shared_ptr<Item> &item) {

    for (auto &task: tasks) {
        task.Control_task(item);
        int reward = 0;
        vector<shared_ptr<Item>> prizes = task.Get_reward(reward);
        if (!prizes.empty()) {
            for (auto &prize: prizes) {
                if (!inventory.Put_in_backpack(prize)) {
                    break;
                }
            }
        }


    }
    //Deletion of completed tasks
    Delete_completed(tasks);
    return inventory.Put_in_backpack(item);

}

//Main user interaction with monsters
bool User::Interaction(vector<shared_ptr<Character>> &monsters) {
    clear();

    //Interaction starting with checking tasks, if some monsters are same as user is looking for, user will get reward, in case of loose he just loose those items/reward
    for (auto &task: tasks) {
        for (size_t i = 2; i < monsters.size(); i++) {
            task.Control_task(monsters[i]);
            task.Get_reward(monsters[1]);
        }
    }

    Delete_completed(tasks);

    //Three basic interaction, basic attack, special abilities and using heal items
    printw("1: Attack Monsters\n");
    printw("2: Use special abilities\n");
    printw("3: Use healing items\n");
    printw("Your input: ");
    refresh();

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long ch = int_input_conversion();


        if (ch > 3 || ch < 1) {
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
                case attack:
                    Attack(monsters);
                    break;
                case abilities:
                    User_Using_abilities(monsters);
                    break;
                case invent:
                    Using_heal_items(monsters);
                    break;

            }
            // in case of all monsters dead program is checking if user's exp isn't enough for upgrading level
            if (monsters.size() == 2) {
                while (exp >= exp_next) {
                    clear();
                    printw("Now your level is %d\n", level + 1);
                    refresh();
                    Upgrade_level();
                }
            }
            clear();
            flushinp();
            refresh();
            break;
        }

    }
    return true;
}

//In fact almost the same as distributing points in new_character in game.cpp
void User::Upgrade_level() {

    exp -= exp_next;
    level++;
    exp_next += 1;
    exp_next *= 2;
    Attributes new_skills(perks);
    new_skills.points_to_distribute += 1;
    new_skills.Print_to_screen();
    printw("%zu: Skip points distributing\n", new_skills.skills_count() + 1);
    printw("Your input : ");

    refresh();


    while (new_skills.points_to_distribute > 0) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long character = int_input_conversion();
        character--;
        if (character > static_cast<long int>(new_skills.skills_count()) || character < 0) {
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
        //In case of skip just increase level
        if (character == static_cast<long int>(new_skills.skills_count())) {
            while (exp >= exp_next) {
                exp -= exp_next;
                level++;
                exp_next += 1;
                exp_next *= 2;
            }

            clear();
            refresh();
            break;
        } else {
            clear();
            if (!new_skills.use_free_points(static_cast<int>(character))) {
                printw("Not enough points for this skill\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                clear();
            }


            clear();


            refresh();
            flushinp();
            break;

        }

    }
    perks = new_skills;
    clear();
    refresh();

}

//Attacking monsters with basic attack
void User::Attack(vector<shared_ptr<Character>> &monsters) {

    clear();
    size_t ip = 2;
    for (; ip < monsters.size(); ip++) {
        const auto &mon = monsters[ip];
        printw("%zu: Attack Monster %s with %d HP \n", ip - 1, mon->get_name().c_str(), mon->get_HP());

    }
    printw("%zu: Back to menu\n", ip - 1);
    printw("Your input: ");
    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long ch = int_input_conversion();
        ch++;
        //right number starts after second element of vector and ends after vector's size
        //in case of wrong number on input ch will be 1 after increasing, and it is also a wrong input
        if (ch > static_cast<long int>(monsters.size()) || ch < 1) {
            printw(" wrong num: %ld , try again", ch - 1);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();
            flushinp();
            refresh();
            continue;
        }
        //in case of ch equals to size of vector user is returning to previous menu recursively
        if (ch == static_cast<long int>(monsters.size())) {
            clear();
            refresh();
            Interaction(monsters);
            break;
        } else {
            //In case of successful controls user deals damage to monster
            monsters[ch]->TakeDamage(damage);
            clear();
            printw("You dealt %d damage to %s\n", static_cast<int>(damage * (1 - (monsters[ch]->get_defence() * 0.01))),
                   monsters[ch]->get_name().c_str());
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            //and if monster is dead, we delete him from vector
            if (monsters[ch]->get_HP() == 0) {

                monsters.erase(monsters.begin() + ch);

            }
            flushinp();
            clear();
            refresh();
            break;
        }

    }
}

void User::Print_tasks(std::ostream &os) {

    os << std::endl;
    for (const auto &task: tasks) {
        task.Print(os);
    }
    os << std::endl;


}

//When we add money to user, we also increase exp
void User::add_Money(int Money) {

    if (Money > 0) {
        exp += Money;
    }
    money += Money;

}

void User::Print(std::ostream &os) {

    os << "archetype is " << archetype.class_name << " ";
    Character::Print(os);
    perks.Print(os);
    os << "money: " << money << " exp: " << exp << " exp_next: " << exp_next << endl;


}

void User::User_Using_abilities(vector<shared_ptr<Character>> &monsters) {
    std::ostringstream os;

    clear();
    printw("Your archetype is %s\n", archetype.class_name.c_str());
    printw("Which effect do you wanna use ?\n");
    archetype.Print(os);
    printw("%s\n", os.str().c_str());
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print the name of effect for using: ");
    refresh();
    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        //finding effect in archetype effects
        shared_ptr<Effect> eff = archetype.find_effect(bufffer);
        //if its nullptr, then there is no such effect, or it's a passive effect
        if (eff != nullptr) {
            clear();

            eff->apply_effect(monsters);


            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            Interaction(monsters);
            break;
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

void User::Using_heal_items(vector<shared_ptr<Character>> &monsters) {

    clear();

    std::ostringstream os;
    if (!Print_heal_items(os)) {
        os << "No heal items in your inventory\n";
    }
    printw("%s", os.str().c_str());
    printw("You have %d HP left\n", HP);
    printw("Print \"Back\" for turning back to menu\n");
    printw("For using item print it's name: ");
    refresh();

    char buffer[256];
    int heal_effect;

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(buffer, sizeof(buffer) - 1);
        //Looking for heal item in backpack, if it exists, method will return true and set heal_effect to right value
        if (Use_heal_item(buffer, heal_effect)) {
            Heal(heal_effect);
            printw("You have %d HP left\n", HP);


            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            clear();
            break;
        }
        if (string(buffer) == "Back") {
            clear();
            refresh();
            Interaction(monsters);
            break;
        } else {
            printw("Wrong input :%s , try again", buffer);
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

void User::Inventory_use() {
    clear();
    refresh();





    ///You can delete item only after putting it to inventory
    printw("1: Take out weapon\n");
    printw("2: Put weapon back\n");
    printw("3: Put on armour\n");
    printw("4: Put armour back to inventory\n");
    printw("5: Throw the item from inventory\n");
    printw("6: Move items from/to additional containers\n");
    printw("7: Previous menu\n");
    printw("Your money: %d\n", money);
    printw("Your input: ");
    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        long ch = int_input_conversion();


        if (ch == Previous_menu) {
            break;
        }
        if (ch > 7 || ch < 1) {
            printw("Wrong num :%ld, try again\n", ch);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();

            continue;
        }


        if (ch == Weapon_on) {
            Weapon_On();

            break;
        }
        if (ch == Weapon_off) {
            Weapon_Off();

            break;
        }
        if (ch == Armour_on) {
            Armour_On();

            break;
        }
        if (ch == Armour_off) {
            Armour_Off();

            break;
        }
        if (ch == Delete_item) {
            Delete_Item();

            break;
        }
        if (ch == Item_saver_usement) {
            if (!Item_saver_use()) {
                printw("You dont have any additional container\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }

            break;
        }


        clear();
        refresh();
        break;


    }

}

bool User::Item_saver_use() {
    if (!inventory.Item_saver_use()) {
        return false;
    }
    return true;
}

void User::Weapon_On() {
    refresh();
    clear();
    refresh();
    std::ostringstream os;
    if (inventory.Print_Weapons_Backpack(os)) {
        printw("%s", os.str().c_str());
    } else {
        printw("No weapons in your inventory\n");

    }
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of weapon to put in arm with worst damage  :");
    refresh();

    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        //Same method as for effects
        shared_ptr<Item> it = inventory.find_item(bufffer, Backpack_cont);
        if (it != nullptr) {
            clear();
            inventory.Delete_Item(it, Backpack_cont);
            printw("damage before %d\n", damage);
            //we are putting every weapon in a hand with less damage
            if (Left_hand_dmg > Right_hand_dmg) {
                Put_in_Right_hand(it);
            } else {
                Put_in_left_hand(it);
            }
            std::ostringstream os1;


            printw("damage after %d\n", damage);


            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            Inventory_use();
            break;
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

void User::Weapon_Off() {
    bool Left = false;
    refresh();
    clear();
    refresh();
    std::ostringstream os;
    if (inventory.Print_Weapons_Arms(os)) {
        printw("%s", os.str().c_str());
    } else {
        printw("No weapons in your hands\n");
    }

    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of weapon to put it in inventory :");
    refresh();

    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        shared_ptr<Item> it;
        //Looking for item in both hands
        if ((it = inventory.find_item(bufffer, 1)) == nullptr) {
            it = inventory.find_item(bufffer, 0);
            Left = true;
        }
        if (it != nullptr) {

            clear();

            printw("damage before %d\n", damage);

            if (Left) {
                //Checking if user have enough space in backpack to put weapon in it
                if (inventory.Full(Left_arm) && inventory.Full(Backpack_cont)) {
                    printw("No space left in your hand and in your inventory, please throw out some item from backpack before putting new item in backpack\n");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                    Inventory_use();
                    return;
                }
                //if user have enough space we put item in backpack and delete it from hand
                damage -= Left_hand_dmg;
                Left_hand_dmg = 0;
                Put_in_backpack(it);
                inventory.Delete_Item(it, Left_arm);
            }
            if (!Left) {
                //Checking if user have enough space in backpack to put weapon in it
                if (inventory.Full(Right_arm) && inventory.Full(Backpack_cont)) {
                    printw("No space left in your hand and in your inventory, please throw out some item from backpack before putting new item in backpack\n");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
                    Inventory_use();
                    return;
                }
                //Same as for another hand
                damage -= Right_hand_dmg;
                Right_hand_dmg = 0;
                Put_in_backpack(it);
                inventory.Delete_Item(it, Right_arm);
            }


            refresh();
            printw("damage after %d\n", damage);


            refresh();


            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            Inventory_use();
            break;
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

void User::Armour_On() {
    refresh();
    clear();
    refresh();
    std::ostringstream os;
    if (inventory.Print_Armour_Backpack(os)) {
        printw("%s", os.str().c_str());
    } else {
        printw("No armour in your inventory\n");

    }
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of armour item to put it on you :");
    refresh();

    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        shared_ptr<Item> it = inventory.find_item(bufffer, Backpack_cont);
        if (it != nullptr) {
            clear();
            printw("defence before %d\n", defence);
            shared_ptr<Item> it2 = it;
            //Handling situation with wrong item
            if (!Put_on_armour(it)) {
                printw("Wrong input :%s , try again", bufffer);
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();
                continue;
            }
            //if we put item successfully , we should delete it from backpack
            inventory.Delete_Item(it2, Backpack_cont);
            printw("defence after %d\n", defence);


            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            Inventory_use();
            break;
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

void User::Armour_Off() {
    clear();
    refresh();
    std::ostringstream os;
    inventory.Print(os,Armour_container);
    printw("%s", os.str().c_str());

    //Handling situation with full backpack
    if (inventory.Full(Backpack_cont)) {
        printw("No space left on you and in your inventory, please throw out some item from backpack before putting new item in backpack\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
        Inventory_use();
        return;
    }
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of armour item to put it in inventory :");
    refresh();

    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);

        shared_ptr<Item> it = inventory.find_item(bufffer, Armour_container);

        if (it != nullptr) {
            shared_ptr<Item> it2 = it;
            clear();

            printw("defence before %d\n", defence);
            defence -= it->get_info();
            if (Put_in_backpack(it)) {
                inventory.Delete_Item(it2, Armour_container);


                refresh();
                printw("defence after %d\n", defence);


                refresh();


                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            }
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            Inventory_use();
            break;
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

void User::Delete_Item() {
    clear();
    refresh();
    std::ostringstream os;
    if (inventory.Print(os, Backpack_cont)) {
        printw("%s", os.str().c_str());
    } else {
        printw("Your backpack is empty\n");
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Inventory_use();
        return;
    }
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of item to throw it away :");
    char bufffer[256];
    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);

        shared_ptr<Item> it = inventory.find_item(bufffer, Backpack_cont);

        if (it != nullptr) {

            clear();


            inventory.Delete_Item(it, Backpack_cont);


            refresh();


            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            break;
        }
        if (string(bufffer) == "Back") {
            clear();
            refresh();
            Inventory_use();
            break;
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

//adding tasks to user from npc
bool User::addTask(bool Finished, const string &Task_name, const string &Task_description, int award,
                   const vector<shared_ptr<Item>> &prizes, Type type, const shared_ptr<Character> &person_to_find,
                   const shared_ptr<Item> &item_to_find, const shared_ptr<Character> &monster_to_find,
                   vector<Skill> &skills) {
    switch (type) {

        case Type_NPC: {
            Task new_task(Task_name, Task_description, person_to_find, skills);
            if (!new_task.Enough_skills(perks)) {
                return false;
            }
            new_task.award = award;
            new_task.prizes = prizes;
            tasks.push_back(new_task);
        }
            break;
        case Type_item: {
            Task new_task(Task_name, Task_description, item_to_find, skills);
            if (!new_task.Enough_skills(perks)) {
                return false;
            }
            new_task.award = award;
            new_task.prizes = prizes;
            tasks.push_back(new_task);
        }
            break;
        case Type_monster: {
            Task new_task(Task_name, Task_description, monster_to_find, 3, skills);
            if (!new_task.Enough_skills(perks)) {
                return false;
            }
            new_task.award = award;
            new_task.prizes = prizes;
            tasks.push_back(new_task);
        }
            break;
        case Default:
            break;
    }
    clear();
    return true;


}