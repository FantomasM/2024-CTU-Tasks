//
// Created by fantomasm on 25.5.23.
//



#ifndef SEMESTRAL_WORK_OBJECT_H
#define SEMESTRAL_WORK_OBJECT_H

#include <utility>
#include "Character.h"

class Object {
public:
    Object(std::string name, std::string description, std::string detailed_description) : Object_name(std::move(name)),
                                                                                          Object_describe(std::move(
                                                                                                  description)),
                                                                                          Object_detailed_describe(
                                                                                                  std::move(
                                                                                                          detailed_description)) {}

    Object(std::string name, std::string description, std::string detailed_description,
           std::vector<std::shared_ptr<Item>> Items) : Object_name(std::move(name)),
                                                       Object_describe(std::move(description)),
                                                       Object_detailed_describe(std::move(detailed_description)),
                                                       items(std::move(Items)) {}

    Object() : Object_name("Default"), Object_describe("Default describe"),
               Object_detailed_describe("Default detailed describe") {}


    bool Is_destroyed() const;

    void from_json(nlohmann::json json);

    void to_json(nlohmann::json &json);

    void Print(std::ostream &os) const;

    void Print_descr(std::ostream &os) const;

    void Print_items(std::ostream &os) const;

    void Interaction(std::shared_ptr<Character> &character);

    void Look() const;

private:
    void Destroy(std::shared_ptr<Character> &character);

    void Give_items(std::shared_ptr<Character> &character);

    bool destructible = false;
    bool after_destruction = false;
    bool destroyed = false;

    std::string Object_name;
    std::string Object_describe;
    std::string Object_detailed_describe;
    std::vector<std::shared_ptr<Item>> items;

};

#endif //SEMESTRAL_WORK_OBJECT_H
