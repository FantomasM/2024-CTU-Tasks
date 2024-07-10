//
// Created by fantomasm on 10.5.23.
//

#ifndef SEMESTRAL_WORK_DIALOGUES_H
#define SEMESTRAL_WORK_DIALOGUES_H

#include "ncurses.h"
#include "json.hpp"
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

class Dialogue_manager;


class Dialogue {
public:
    Dialogue() : Dialogues_text("Default") {}

    Dialogue(std::string text, std::vector<std::pair<std::string, std::string>> responses) : Dialogues_text(
            std::move(text)), Dialogues_responses(std::move(responses)) {}

    void run();

    void from_json(const nlohmann::json &json);

    void to_json(nlohmann::json &json);


    std::string Dialogues_text;

    std::vector<std::pair<std::string, std::string>> Dialogues_responses;
private:


};


#endif //SEMESTRAL_WORK_DIALOGUES_H