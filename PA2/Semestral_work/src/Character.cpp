//
// Created by fantomasm on 3.5.23.
//
#include <random>

enum container {
    left_arm, right_arm, armor_cont, backpack
};

#include "Character.h"

Character::Character() : hp::hp(1, 1), level(1), default_damage(0), damage(0), defence(0), name("None") {}

Character::Character(int Level, Attributes &Perks, int Damage, int Defence, int hp, int hpmax, string Name) : hp::hp(hp,
                                                                                                                     hpmax),
                                                                                                              level(Level),
                                                                                                              default_damage(
                                                                                                                      Damage),
                                                                                                              damage(Damage),
                                                                                                              defence(Defence),
                                                                                                              name(std::move(
                                                                                                                      Name)) {


}

int Character::get_level() const {

    return level;

}

//function for handing number input
long int_input_conversion() {
    char input[10];
    char *end;
    getnstr(input, sizeof(input) - 1);
    long int number = strtol(input, &end, 10);
    return number;
}

//Getters
void Character::add_Money(int Money) {

    money += Money;

}

int Character::get_Money() const {

    return money;

}

int Character::get_defence() const {

    return defence;

}

Character::~Character() {
    name.clear();
}

int Character::get_def_damage() const {

    return default_damage;

}

std::string Character::get_name() const {

    return name;

}

//Basic print function prints basic information and info about inventory
void Character::Print(std::ostream &os) {

    os << "name is " << name << " level is " << level << " damage is " << damage << " and defence is " << defence
       << std::endl;
    inventory.Print(os);

}

//== operator used in tasks, comparing only name of character and level
bool Character::operator==(const Character &other) {

    if (name == other.name && level == other.level) {
        return true;
    }
    return false;

}

bool Character::Put_in_backpack(std::shared_ptr<Item> &item) {


    return inventory.Put_in_backpack(item);

}

bool Character::Increase_stat(const Skill &ski, int increase_mod) {
    return perks.activate_bonus_int(ski, increase_mod);


}

//Printing heal items from backpack, returns true if os is not empty
bool Character::Print_heal_items(std::ostream &os) {

    inventory.Print_heal_items(os);
    if (os.good()) {
        return true;
    }
    return false;

}

bool Character::Use_heal_item(std::string Name, int &heal_effect) {

    return inventory.Use_heal_item(Name, heal_effect);

}

//returning info about fullness of containers like left arm, right arm, armour container and backpack
bool Character::Full_Inventory(int num) {

    return inventory.Full(num);

}

//Same for count of free places
int Character::Free_places(int num) {

    return inventory.free_places(num);

}

//Increasing damage, used in effects
void Character::Change_Damage(double modifikator) {
    damage = static_cast<int>(damage * modifikator);
}

//Conversion to/from json format
void Character::Save_character_json_opened(nlohmann::json &json) {
    json["level"] = level;
    json["damage"] = damage;
    json["defence"] = defence;
    json["HP"] = HP;
    json["HPmax"] = MaxHP;

    for (const auto &inv: inventory.Inv) {
        json["inventory"].push_back(inv->convertToJson());
    }
    json["name"] = name;
}

bool Character::Save_character_json(string Filename) {
    nlohmann::json json;


    Filename += "character";

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

void Character::Load_character_json_opened(const nlohmann::json &jsonData) {
    name = jsonData["name"];
    level = jsonData["level"];
    damage = jsonData["damage"];
    default_damage = damage;
    defence = jsonData["defence"];
    HP = jsonData["HP"];
    MaxHP = jsonData["HPmax"];

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
}

bool Character::Load_character_json(std::string Filename) {


    Filename += "character";

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
    //}
}

//changed taking damage, defence is used to reduce damage, from 1 to 100 percent
void Character::TakeDamage(int Damage) {
    int Defence = defence;
    if (defence > 100) {
        Defence = 100;
    }

    if (Damage * (1 - (Defence * 0.01)) > HP) {
        HP = 0;
        return;
    }
    HP -= static_cast<int>(Damage * (1 - (Defence * 0.01)));
}

//Using inventory for monster, in case of low hp he tries to find heal_items and use it
void Character::Inventory_use() {

    if (MaxHP / 4 > HP && HP != 0) {
        HP += inventory.Use_any_heal_item();
    }


}

//Putting item in left hand
//In case of true returned by inventory.Put_in_the_left_hand it means that arm was empty before
//In case of false new item is put in arm, and item shared_ptr is now pointing to item, what was in arm before, so we need to put in backpack
//Also we can put only weapons in arms
bool Character::Put_in_left_hand(std::shared_ptr<Item> &item) {
    if (item->get_class_name() == "Weapon") {
        int new_damage = item->get_info();
        if (inventory.Put_in_left_hand(item)) {
            damage += new_damage;
            Left_hand_dmg = new_damage;
        } else {
            damage -= Left_hand_dmg;
            damage += new_damage;
            Left_hand_dmg = new_damage;
            Put_in_backpack(item);


        }
        default_damage = damage;
        return true;
    }
    return false;

}

//Basic interaction for monster
//Deals random damage
bool Character::Interaction(vector<shared_ptr<Character>> &monsters) {
    if (!Paralysed) {
        std::random_device rd;
        std::mt19937 gen(rd());


        std::uniform_int_distribution<int> distribution(damage, damage + 10);


        int randomNumber = distribution(gen);
        if (monsters.size() >= 3) {
            monsters[1]->TakeDamage(randomNumber);
            printw("Monster %s dealt you %d damage \n", name.c_str(),
                   static_cast<int>(randomNumber * (1 - (monsters[1]->get_defence() * 0.01))));
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            return true;
        } else {
            return false;
        }
    }
    printw("Monster %s is paralyzed on this turn \n", name.c_str());
    refresh();
    Paralysed = false;
    return true;
}

//Same as for left hand
bool Character::Put_in_Right_hand(std::shared_ptr<Item> &item) {
    if (item->get_class_name() == "Weapon") {
        int new_damage = item->get_info();
        if (inventory.Put_in_Right_hand(item)) {
            damage += new_damage;
            Right_hand_dmg = new_damage;
        } else {
            damage -= Right_hand_dmg;
            damage += new_damage;
            Right_hand_dmg = new_damage;
            Put_in_backpack(item);


        }
        default_damage = damage;
        return true;
    }
    return false;

}

//Putting armour on character
//Don't accept not armour
//same as for arms, if inventory.Put_on_armour returns true, then such place was empty before
//In opposite situation item pointer is now pointing to new item and we should put it into backpack
bool Character::Put_on_armour(std::shared_ptr<Item> &item) {
    if (item->get_class_name().rfind("Armour", 0) == 0 && item->get_class_name().back() >= '0' &&
        item->get_class_name().back() <= '5') {
        int old_defence = item->get_info();
        if (inventory.Put_on_armour(item)) {
            defence += item->get_info();
        } else {
            defence -= item->get_info();
            defence += old_defence;
            Put_in_backpack(item);
        }
        return true;
    }
    return false;

}

//Market function for user to sell items
//Different declaration in Normal_NPC
void Character::Market(shared_ptr<Character> &person) {
    clear();
    refresh();
    printw("List of selling items: \n");
    std::ostringstream os;
    inventory.Print(os, Backpack_cont);
    printw("%s", os.str().c_str());
    printw("Print name of item to sell it :");
    refresh();
    char bufffer[256];


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        shared_ptr<Item> it = inventory.find_item(bufffer, 3);
        if (it != nullptr) {


            clear();
            refresh();
            person->Put_in_backpack(it);
            inventory.Delete_Item(it, Backpack_cont);
            printw("You successfully sell %s\n", it->Item_name.c_str());
            money += it->get_sell_value();

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
        }

    }
}