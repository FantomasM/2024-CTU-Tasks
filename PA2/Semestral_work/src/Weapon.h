//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_WEAPON_H
#define SEMESTRAL_WORK_WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    inline Weapon(const std::string &name, int Buy_value, int Sell_value, int Damage) : Item(name, Buy_value,
                                                                                             Sell_value),
                                                                                        damage(Damage) {}

    Weapon() = default;

    ~Weapon() = default;

    inline bool IsWeapon() const override { return true; }

    void Print(std::ostream &os) override;

    const std::string class_name = "Weapon";

    int get_info() const override;

    std::string get_class_name() const override;

    nlohmann::json to_json() const override;

    void from_json(nlohmann::json jsonItem) override;

private:

    int damage = 1;
};

#endif //SEMESTRAL_WORK_WEAPON_H
