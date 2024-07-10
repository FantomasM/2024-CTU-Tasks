//
// Created by fantomasm on 25.5.23.
//

#include "Object.h"

void Object::from_json(nlohmann::json json) {
    Object_name = json["Object_name"];
    Object_describe = json["Object_describe"];
    Object_detailed_describe = json["Object_detailed_describe"];
    destructible = json["destructible"];
    after_destruction = json["after_destruction"];


    if (!json["items"].is_null() && !json["items"].empty()) {
        for (const auto &item: json["items"]) {

            std::string className = item["Class_name"];


            ItemPtr obj = ItemFactory::create(className);


            obj->from_json(item);

            items.push_back(obj);
        }
    }
}

bool Object::Is_destroyed() const {

    return destroyed;

}

void Object::to_json(nlohmann::json &json) {
    json["Object_name"] = Object_name;
    json["Object_describe"] = Object_describe;
    json["Object_detailed_describe"] = Object_detailed_describe;
    json["destructible"] = destructible;
    json["after_destruction"] = after_destruction;

    json["items"] = nullptr;

    for (const auto &item: items) {
        json["items"].push_back(item->to_json());
    }
}

void Object::Print(ostream &os) const {
    os << Object_name << std::endl;
    os << Object_describe << std::endl;
}

void Object::Print_descr(ostream &os) const {
    os << Object_name << std::endl;
    os << Object_detailed_describe << std::endl;
}

void Object::Print_items(ostream &os) const {
    os << "You get " << std::endl;
    for (const auto &item: items) {
        os << item->Item_name << std::endl;
    }
    os << std::endl;
}

//when item is destroyed, its items are given to character
void Object::Destroy(shared_ptr<Character> &character) {
    clear();
    refresh();

    if (after_destruction) {
        if (!items.empty()) {
            clear();
            std::ostringstream os;
            Print_items(os);
            printw("%s\n", os.str().c_str());
            refresh();
            for (auto &item: items) {
                character->Put_in_backpack(item);
            }
        }
        items.clear();
    }
    printw("%s is now destroyed\n", Object_name.c_str());
    refresh();
    destroyed = true;
}

void Object::Give_items(std::shared_ptr<Character> &character) {
    if (!items.empty()) {
        clear();
        std::ostringstream os;
        Print_items(os);
        printw("%s\n", os.str().c_str());
        refresh();
        for (auto &item: items) {
            character->Put_in_backpack(item);
        }
        items.clear();
    }
}

void Object::Interaction(std::shared_ptr<Character> &character) {
    clear();
    refresh();
    printw("Look: Look closer\n");
    if (!items.empty() && !destructible) {
        printw("Items: Take items from %s\n", Object_name.c_str());
    }
    if (destructible) {
        printw("Destroy: Destroy item and take resources from it\n");
    }
    printw("Back : For getting in previous menu\n");
    printw("Your input: ");
    refresh();
    char bufffer[256];


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);


        if (string(bufffer) == "Look") {
            Look();
            Interaction(character);
            break;

        }
        //User can destroy or take items from objects only if he has enough space
        if (string(bufffer) == "Items" && !items.empty() && !destructible) {
            if (character->Free_places(Backpack_cont) < (static_cast<int>(items.size()))) {
                printw("Not enough space in your backpack\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();
                continue;
            }
            Give_items(character);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            Interaction(character);
            break;
        }
        if (string(bufffer) == "Destroy" && destructible) {
            if (character->Free_places(Backpack_cont) < static_cast<int>(items.size())) {
                printw("Not enough space in your backpack\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();
                continue;
            }
            Destroy(character);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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

//Printing full description of item
void Object::Look() const {
    clear();
    refresh();
    std::ostringstream os;
    Print_descr(os);
    printw("%s\n", os.str().c_str());
    printw("Back : For getting in previous menu\n");
    printw("Your input: ");
    refresh();
    char bufffer[256];
    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);


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