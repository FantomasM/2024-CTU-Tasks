//
// Created by fantomasm on 4.5.23.
//
#pragma once
#ifndef UNTITLED8_ITEM_H
#define UNTITLED8_ITEM_H

#include <memory>
#include <vector>
#include <utility>
#include <iostream>
#include <unordered_map>
#include <ncurses.h>
#include <json.hpp>
#include "Attributes.h"

#endif //UNTITLED8_ITEM_H

class Item {
public:
    inline Item(std::string name, int Buy_value, int Sell_value) : Item_name(std::move(name)), buy_value(Buy_value),
                                                                   sell_value(Sell_value) {}

    inline virtual bool IsHealingItem() const { return false; }

    inline virtual bool IsWeapon() const { return false; }

    inline virtual bool IsArmour() const { return false; }

    inline virtual bool IsItemSaver() const { return false; }

    virtual Item &operator+=(const Item &item);

    virtual Item &operator+=(const std::shared_ptr<Item> &item);

    virtual std::shared_ptr<Item> operator-(const Item item);

    Item();

    ~Item();

    bool operator==(const Item &it) const;

    virtual void Print(std::ostream &os);


    virtual std::string get_class_name() const {
        return class_name;
    }

    virtual int get_info() const {
        return buy_value;
    }

    inline int get_buy_value() const {
        return buy_value;
    }

    inline int get_sell_value() const {
        return sell_value;
    }


    virtual nlohmann::json to_json() const;

    virtual void from_json(nlohmann::json jsonItem);

    std::string Item_name;
private:
    std::string class_name = "Default";
protected:

    int buy_value;
    int sell_value;
};







