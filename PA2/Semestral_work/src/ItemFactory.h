//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_ITEMFACTORY_H
#define SEMESTRAL_WORK_ITEMFACTORY_H

#include "Weapon.h"
#include "Armour.h"
#include "Food.h"
#include "Item_saver.h"
#include "Valuables.h"
//Factory class to read item elements from json files
using ItemPtr = std::shared_ptr<Item>;

class ItemFactory {
public:
    static ItemPtr create(const std::string &class_name);
};

#endif //SEMESTRAL_WORK_ITEMFACTORY_H
