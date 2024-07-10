//
// Created by fantomasm on 28.5.23.
//
enum armour_part {
    helmet, chest_plate, gloves, boots, armoured_pants, amulet
};

#ifndef SEMESTRAL_WORK_ARMOUR_H

#include "Item.h"

#define SEMESTRAL_WORK_ARMOUR_H

class Armour : public Item {
public:
    inline Armour(const std::string &name, int Buy_value, int Sell_value, int Defence, armour_part part) : Item(name,
                                                                                                                Buy_value,
                                                                                                                Sell_value),
                                                                                                           Part(part),
                                                                                                           defence(Defence) {
    }

    Armour() = default;

    inline Armour(const std::string &name, int Buy_value, int Sell_value, int Defence, int part) : Item(name, Buy_value,
                                                                                                        Sell_value),
                                                                                                   Part(
                                                                                                           static_cast<armour_part>(part)),
                                                                                                   defence(Defence) {}

    ~Armour() = default;

    inline bool IsArmour() const override { return true; }

    void Print(std::ostream &os) override;

    std::string class_name = "Armour";
    armour_part Part = amulet;

    int get_info() const override;

    std::string get_class_name() const override;

    nlohmann::json to_json() const override;

    void from_json(nlohmann::json jsonItem) override;

private:
    int defence = 1;

};

#endif //SEMESTRAL_WORK_ARMOUR_H
