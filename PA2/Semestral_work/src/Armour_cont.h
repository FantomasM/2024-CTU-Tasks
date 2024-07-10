//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_ARMOUR_CONT_H

#include "Items_container.h"

#define SEMESTRAL_WORK_ARMOUR_CONT_H

class Armour_cont : public Items_container {
public:
    Armour_cont() : Items_container(6) {}

    Armour_cont(std::string Name) : Items_container(6) { name_of_container = std::move(Name); }

    bool Remove_Item(const std::shared_ptr<Item> &item) override;

    bool Add_Item(std::shared_ptr<Item> &item) override;

    std::string get_class_name() override;

private:
    const std::string Class_name = "Armour_cont";
};

#endif //SEMESTRAL_WORK_ARMOUR_CONT_H
