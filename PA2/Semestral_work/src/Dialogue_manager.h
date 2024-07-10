//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_DIALOGUE_MANAGER_H
#define SEMESTRAL_WORK_DIALOGUE_MANAGER_H

#include "thread"
#include "Dialogues.h"

class Dialogue_manager {

public:
    Dialogue_manager() : current_dialogue("None") {}

    void addDialogue(const std::string &dialogueName, const Dialogue &dialogue);

    void from_json(const nlohmann::json &json);

    void to_json(nlohmann::json &json);

    void start_Dialogue();

    void Dialogue_run(Dialogue &dial);

    void Restart_dialogue();

private:
    std::unordered_map<std::string, Dialogue> dialogues;
    std::string current_dialogue = "Empty";
    std::string start_dialogue = "Empty";
};

#endif //SEMESTRAL_WORK_DIALOGUE_MANAGER_H
