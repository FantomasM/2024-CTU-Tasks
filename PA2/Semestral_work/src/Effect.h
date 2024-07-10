//
// Created by fantomasm on 3.5.23.
//


#ifndef UNTITLED8_CLASS_H
#define UNTITLED8_CLASS_H

#include <memory>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>


using namespace std;

#include "json.hpp"
#include "Attributes.h"
#include "Character.h"

class Effect {
public:
    Effect() : name_of_effect("Default") {}

    ~Effect() = default;

    virtual void apply_effect(vector<shared_ptr<Character>> &Char) = 0;

    virtual nlohmann::json to_json();

    virtual void from_json(nlohmann::json effect);

    virtual void Print(std::ostream &os) {

        os << "effect's name is " << name_of_effect << std::endl;
    }


    std::string name_of_effect;
    std::string Class_name = "Effect";
    bool active = true;
};


#endif //UNTITLED8_CLASS_H