//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_BACKPACK_H
#define SEMESTRAL_WORK_BACKPACK_H

#include "Items_container.h"

class Backpack : public Items_container {
public:
    Backpack() : Items_container(10) {}

    Backpack(std::string Name) : Items_container(10) { name_of_container = Name; }

    Backpack(int Capacity, std::string Name) : Items_container(Capacity) { name_of_container = Name; }

    std::string get_class_name() override;

    const std::string Class_name = "Backpack";
};

#endif //SEMESTRAL_WORK_BACKPACK_H
