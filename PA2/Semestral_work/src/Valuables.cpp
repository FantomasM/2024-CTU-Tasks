//
// Created by fantomasm on 28.5.23.
//

#include "Valuables.h"

void Valuables::Print(std::ostream &os) {
    Item::Print(os);

}

std::string Valuables::get_class_name() const {
    return class_name;
}

int Valuables::get_info() const {

    return sell_value;

}