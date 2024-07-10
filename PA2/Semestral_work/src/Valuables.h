//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_VALUABLES_H
#define SEMESTRAL_WORK_VALUABLES_H

#include "Item.h"

class Valuables : public Item {
public:
    inline Valuables(const std::string &name, int Buy_value, int Sell_value) : Item(name, Buy_value, Sell_value) {}

    Valuables() = default;

    ~Valuables() = default;

    void Print(std::ostream &os) override;

    const std::string class_name = "Valuables";

    std::string get_class_name() const override;

    int get_info() const override;

private:

};

#endif //SEMESTRAL_WORK_VALUABLES_H
