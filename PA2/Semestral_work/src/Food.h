//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_FOOD_H
#define SEMESTRAL_WORK_FOOD_H

#include "Item.h"

class Food : public Item {
public:
    inline Food(const std::string &name, int Buy_value, int Sell_value, int Heal_effect) : Item(name, Buy_value,
                                                                                                Sell_value),
                                                                                           heal_effect(Heal_effect) {}

    Food() = default;

    ~Food() = default;

    void Print(std::ostream &os) override;

    const std::string class_name = "Food";

    int get_info() const override;

    std::string get_class_name() const override;

    nlohmann::json to_json() const override;

    inline bool IsHealingItem() const override { return true; }

    void from_json(nlohmann::json jsonItem) override;

private:
    int heal_effect = 1;
};

#endif //SEMESTRAL_WORK_FOOD_H
