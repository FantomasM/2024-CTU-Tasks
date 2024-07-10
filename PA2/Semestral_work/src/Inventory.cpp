//
// Created by fantomasm on 28.5.23.
//
#define Item_saver_backpack 2
#define Backpack_item_saver 1
#define Back 3

#include "Inventory.h"

void Inventory::Print(std::ostream &os) {
    for (auto &i: Inv) {
        i->Print_Items(os);
    }
}

bool Inventory::Item_saver_use() {
    std::ostringstream os;
    if(Inv.size()<4){
    throw std::out_of_range("Wrong count of allocated resources.");
    }
    if (!Inv[3]->Print_Item_savers(os)) {
        return false;
    }
    clear();
    printw("List of additional containers:\n%s\n", os.str().c_str());

    printw("Print name of container to interact with it\n");
    printw("Your input: ");
    refresh();
    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        if (std::string(bufffer) == "Back") {
            clear();
            refresh();

            break;
        }
        std::shared_ptr<Item> it = find_ref(bufffer, Backpack_cont);
        //Finding item_saver item and checking if it is really item_saver

        if (it != nullptr) {
            if (!it->IsItemSaver()) {
                printw("Wrong input, its not a container :%s , try again", bufffer);
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();
                continue;
            }

            Inside_item_saver(it);






            //recursive call to return to the same place after getting back from inside menu
            Item_saver_use();
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
    return true;
}

int Inventory::Use_any_heal_item() {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    std::shared_ptr<Item> it = Inv[3]->find_any_heal_item();
    if (it != nullptr) {
        const std::shared_ptr<Item> &it2 = it;
        Inv[3]->Remove_Item(it);
        return it2->get_info();
    }
    return 0;
}

bool Inventory::Put_in_left_hand(std::shared_ptr<Item> &item) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    return Inv[0]->Add_Item(item);

}

bool Inventory::Put_in_Right_hand(std::shared_ptr<Item> &item) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    return Inv[1]->Add_Item(item);
}

bool Inventory::Put_on_armour(std::shared_ptr<Item> &item) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    return Inv[2]->Add_Item(item);
}

bool Inventory::Put_in_backpack(std::shared_ptr<Item> &item) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    return Inv[3]->Add_Item(item);
}

int Inventory::free_places(int num) {

    if (num < 0 || num > 3) {
        throw std::runtime_error("Trying to access memory out of inventory");
    }
    return Inv[num]->capacity - Inv[num]->num_of_items;

}

bool Inventory::Full(int num) {

    if (num < 0 || num > 3) {
        throw std::runtime_error("Trying to access memory out of inventory");
    }
    return Inv[num]->full();

}

void Inventory::Inside_item_saver(std::shared_ptr<Item> &item_saver) {
    clear();;
    printw("1: Move items from backpack to %s\n", item_saver->Item_name.c_str());
    printw("2: Move item from %s to backpack\n", item_saver->Item_name.c_str());
    printw("3: Return to previous menu\n");
    refresh();
    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        char input[10];
        char *end;
        getnstr(input, sizeof(input) - 1);
        long int ch = strtol(input, &end, 10);


        if (ch > 3 || ch < 1) {
            printw("Wrong num :%ld, try again\n", ch);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y, x);
            clrtoeol();
            refresh();

            continue;
        } else {
            switch (ch) {
                case Backpack_item_saver:
                    backpack_item_saver(item_saver);
                    clear();
                    refresh();
                    Inside_item_saver(item_saver);
                    break;
                case Item_saver_backpack:
                    item_saver_backpack(item_saver);
                    clear();
                    refresh();
                    Inside_item_saver(item_saver);
                    break;
                case Back:

                    break;


            }
            clear();
            refresh();
            break;
        }

    }
}

void Inventory::backpack_item_saver(std::shared_ptr<Item> &item_saver) {
    clear();
    std::ostringstream os;
    Inv[3]->Print_Items(os);
    printw("List of items in backpack:\n");
    printw("%s\n", os.str().c_str());
    printw("Print name of item to move it to %s\n", item_saver->Item_name.c_str());
    printw("Print \"Back\" for turning back to menu\n");
    printw("Your input: ");
    refresh();
    char bufffer[256];

    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        std::shared_ptr<Item> it = find_item(bufffer, Backpack_cont);

        if (it != nullptr) {
            if (it->IsItemSaver()) {
                printw("Wrong input, you can't put container into container , try again");
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
            int old_size = item_saver->get_info();
            *item_saver += it;
            //If size of item saver is the same as before, then adding item was unsuccessful
            //Item saver takes in every type of item except item_saver
            if (old_size == item_saver->get_info()) {
                printw("Container is full, please remove some items from it\n");
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
            Delete_Item(it, 3);


            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            backpack_item_saver(item_saver);
            break;
        }
        if (std::string(bufffer) == "Back") {
            clear();
            refresh();

            break;
        } else {

            printw("Wrong input :%s , try again", bufffer);
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

void Inventory::item_saver_backpack(std::shared_ptr<Item> &item_saver) {
    clear();
    std::ostringstream os;
    item_saver->Print(os);
    printw("List of items in container: \n");
    printw("%s\n", os.str().c_str());
    printw("Print \"Back\" for turning back to menu\n");
    printw("Print name of item to move it to backpack\n");
    printw("Your input: ");
    refresh();
    char bufffer[256];
    refresh();


    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        getnstr(bufffer, sizeof(bufffer) - 1);
        if (std::string(bufffer) == "Back") {


            break;
        } else {
            if(Inv.size()<4){
                throw std::out_of_range("Wrong count of allocated resources.");
            }
            if (Inv[3]->full()) {
                printw("Backpack is full, you must throw out some items\n");
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();
                continue;
            }
            int old_size = item_saver->get_info();
            Item it(bufffer, 1, 1);
            std::shared_ptr<Item> item1 = item_saver->operator-(it);
            if (old_size == item_saver->get_info()) {
                printw("Wrong input :%s , try again", bufffer);
                refresh();
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                move(y + 1, 0);
                clrtoeol();
                move(y, x);
                clrtoeol();
                refresh();
                continue;
            } else {
                if(Inv.size()<4){
                    throw std::out_of_range("Wrong count of allocated resources.");
                }
                Inv[3]->Add_Item(item1);
                item_saver_backpack(item_saver);
                break;
            }

        }


    }
}

bool Inventory::Print(std::ostream &os, int num) {
    if (num < 0 || num > 3) {
        throw std::runtime_error("Trying to access memory out of inventory");
    }
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    Inv[num]->Print_Items(os);
    if (os.fail()) {
        return false;
    }
    return true;
}

bool Inventory::Print_heal_items(std::ostream &os) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    Inv[3]->Print_heal_items(os);

    //if ostream is empty return false
    if (os.fail()) {
        return false;
    }
    return true;
}

bool Inventory::Print_Weapons_Backpack(std::ostream &os) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    Inv[3]->Print_Weapons(os);
    if (os.fail()) {
        return false;
    }
    return true;
}

bool Inventory::Print_Weapons_Arms(std::ostream &os) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    Inv[0]->Print_Weapons(os);
    Inv[1]->Print_Weapons(os);
    if (os.fail()) {
        return false;
    }
    return true;
}

bool Inventory::Print_Armour_Backpack(std::ostream &os) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    Inv[3]->Print_Armour(os);
    if (os.fail()) {
        return false;
    }
    return true;
}


bool Inventory::Delete_Item(const std::shared_ptr<Item> &item, int num) {
    if (num < 0 || num > 3) {
        throw std::runtime_error("Trying to access memory out of inventory");
    }
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    if (Inv[num]->Remove_Item(item)) {
        return true;
    }
    return false;

}

bool Inventory::Use_heal_item(const std::string &name, int &heal_effect) {
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    heal_effect = Inv[3]->delete_heal_item(name);
    if (heal_effect != 0) {
        return true;
    }

    return false;
}

std::shared_ptr<Item> Inventory::find_item(const std::string &name, int num) {
    if (num < 0 || num > 3) {
        throw std::runtime_error("Trying to access memory out of inventory");
    }
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    return Inv[num]->Find_item(name);
}

std::shared_ptr<Item> Inventory::find_ref(const std::string &name, int num) {
    if (num < 0 || num > 3) {
        throw std::runtime_error("Trying to access memory out of inventory");
    }
    if(Inv.size()<4){
        throw std::out_of_range("Wrong count of allocated resources.");
    }
    return Inv[num]->find_ref(name);
}
