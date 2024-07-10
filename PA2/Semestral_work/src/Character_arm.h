//
// Created by fantomasm on 28.5.23.
//
#include <utility>


#ifndef SEMESTRAL_WORK_CHARACTER_ARM_H
#define SEMESTRAL_WORK_CHARACTER_ARM_H

#include "Items_container.h"

class Character_arm : public Items_container {
public:
    Character_arm() : Items_container(1) {}

    Character_arm(std::string Name) : Items_container(1) { name_of_container = std::move(Name); }

    bool Remove_Item(const std::shared_ptr<Item> &item) override;

    bool Add_Item(std::shared_ptr<Item> &item) override;

    std::string get_class_name() override;

private:
    const std::string Class_name = "Character_arm";
};

#endif //SEMESTRAL_WORK_CHARACTER_ARM_H
