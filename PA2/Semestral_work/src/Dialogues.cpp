//
// Created by fantomasm on 10.5.23.
//

#include "Dialogues.h"

void Dialogue::run() {
    clear();
    refresh();
    printw("%s\n", Dialogues_text.c_str());
    printw("Responses :\n");
    size_t pos = 1;
    for (const auto &dialogue: Dialogues_responses) {
        printw("%zu: %s\n", pos, dialogue.first.c_str());
        pos++;
    }
    printw("%zu: Exit from dialogue\n", pos);
    refresh();

}

void Dialogue::from_json(const nlohmann::json &json) {

    Dialogues_text = json["Dialogues_text"];

    if (!json["Dialogues_responses"].is_null() && !json["Dialogues_responses"].empty()) {


        for (const auto &dialogue: json["Dialogues_responses"]) {

            std::string response = dialogue["response"];
            std::string next_dialogue = dialogue["next_dialogue"];
            Dialogues_responses.emplace_back(response, next_dialogue);

        }
    }
}

void Dialogue::to_json(nlohmann::json &json) {
    json["Dialogues_text"] = Dialogues_text;
    json["Dialogues_responses"] = nullptr;
    for (const auto &response: Dialogues_responses) {
        nlohmann::json resp;
        resp["response"] = response.first;
        resp["next_dialogue"] = response.second;
        json["Dialogues_responses"].push_back(resp);
    }

}
