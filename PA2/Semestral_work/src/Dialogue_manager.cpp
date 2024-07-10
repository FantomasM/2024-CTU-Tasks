//
// Created by fantomasm on 28.5.23.
//

#include "Dialogue_manager.h"

//Running dialogue
void Dialogue_manager::Dialogue_run(Dialogue &dial) {
    //Print text of person and possible responses
    dial.run();

    printw("Your input: ");
    while (true) {
        int x = getcurx(stdscr);
        int y = getcury(stdscr);
        char input[10];
        char *end;
        getnstr(input, sizeof(input) - 1);
        long int ch = strtol(input, &end, 10);
        ch--;


        //Handling wrong inputs
        if (0 > ch || ch > static_cast<long int>(dial.Dialogues_responses.size())) {
            printw("Wrong num :%ld, try again\n", ch);
            refresh();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            move(y + 1, 0);
            clrtoeol();
            move(y, x);
            clrtoeol();
            refresh();

            continue;
        }
        if (ch == static_cast<long int>(dial.Dialogues_responses.size())) {
            break;
        }
            //If dialogue has responses and user chooses one, we will move to next dialogue
        else {
            if (!dial.Dialogues_responses.empty() && dial.Dialogues_responses[ch].second != "None") {
                current_dialogue = dial.Dialogues_responses[ch].second;

                start_Dialogue();
            }


        }
        clear();
        refresh();
        break;
    }
}

void Dialogue_manager::addDialogue(const std::string &dialogueName, const Dialogue &dialogue) {


    dialogues[dialogueName] = dialogue;

}

void Dialogue_manager::start_Dialogue() {
    //Finding dialogue in hashmap and run it
    auto it = dialogues.find(current_dialogue);
    if (it != dialogues.end()) {
        Dialogue_run(it->second);
    } else {
        throw std::runtime_error("No such dialogue found: " + current_dialogue);
    }


}

void Dialogue_manager::Restart_dialogue() {

    current_dialogue = start_dialogue;

}

void Dialogue_manager::from_json(const nlohmann::json &json) {
    bool first = true;
    if (!json["dialogues"].is_null() && !json["dialogues"].empty()) {

        for (const auto &dialogue: json["dialogues"]) {
            Dialogue new_dial;
            new_dial.from_json(dialogue);

            addDialogue(new_dial.Dialogues_text, new_dial);
            if (first) {
                current_dialogue = new_dial.Dialogues_text;
                start_dialogue = current_dialogue;
            }
            first = false;


        }
    }
}

void Dialogue_manager::to_json(nlohmann::json &json) {
    json["dialogues"] = nullptr;
    for (auto &dial: dialogues) {
        nlohmann::json dialogue;
        dial.second.to_json(dialogue);
        json["dialogues"].push_back(dialogue);
    }
}