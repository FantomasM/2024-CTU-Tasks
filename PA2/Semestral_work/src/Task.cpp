//
// Created by fantomasm on 24.5.23.
//

#include "Task.h"
#include "Monster.h"
#include "Normal_NPC.h"

bool Task::Control_task(const shared_ptr<Character> &NPC) {
    if (type == Type_NPC) {
        if (*NPC == *person_to_find) {
            Finished = true;
            return true;
        }
        return false;
    }
    if (type == Type_monster) {

        if (*NPC == *monster_to_find) {
            Finished = true;

            return true;
        }
        return false;
    }
    return false;
}

bool Task::operator==(const Task &other) const {

    if (Task_name == other.Task_name && Task_description == other.Task_description && type == other.type) {
        return true;
    }
    return false;

}

bool Task::Control_task(const shared_ptr<Item> &item) {
    if (type == Type_item) {
        if (*item == *item_to_find) {
            Finished = true;
            return true;
        }
    }
    return false;
}


bool Task::from_json(const nlohmann::json &json) {
    Task_name = json["Task_name"];
    Task_description = json["Task_description"];
    Finished = json["Finished"];
    type = json["type"];
    award = json["award"];
    if (!json["NPC"].is_null() && !json["NPC"].empty()) {
        for (const auto &jsonItem: json["NPC"]) {
            std::shared_ptr<Normal_NPC> npc = std::make_shared<Normal_NPC>();
            npc->Load_character_json_opened(jsonItem);
            person_to_find = npc;
        }
    }
    if (!json["Items"].is_null() && !json["Items"].empty()) {
        for (const auto &jsonItem: json["Items"]) {
            std::string className = jsonItem["Class_name"];
            ItemPtr obj = ItemFactory::create(className);
            obj->from_json(jsonItem);
            item_to_find = obj;

        }
    }
    if (!json["Monster"].is_null() && !json["Monster"].empty()) {
        for (const auto &jsonItem: json["Monster"]) {
            //std::shared_ptr<Monster> mon;
            Monster mon;
            mon.Load_character_json_opened(jsonItem);
            monster_to_find = make_shared<Monster>(mon);
        }
    }
    if (!json["perks"].is_null() && !json["perks"].empty()) {
        for (const auto &json_skill: json["perks"]) {
            Skill new_skill;
            new_skill = new_skill.fromJson(json_skill);
            skills_for_task.push_back(new_skill);
        }
    }
    return true;
}

//Control if user have enough skills to start this task
bool Task::Enough_skills(const Attributes &skills) {
    if (skills_for_task.empty()) {
        return true;
    }
    bool Has_all_skills = std::all_of(skills_for_task.begin(), skills_for_task.end(),
                                      [&](const auto &ski) { return skills.Has_such_skill(ski); });

    if (Has_all_skills) {
        return true;
    }

    return false;
}

nlohmann::json Task::to_json() const {
    nlohmann::json json;
    json["Task_name"] = Task_name;
    json["Task_description"] = Task_description;
    json["Finished"] = Finished;
    json["type"] = type;
    json["award"] = award;
    json["NPC"] = nullptr;

    if (person_to_find != nullptr) {
        nlohmann::json json2;
        person_to_find->Save_character_json_opened(json2);
        json["NPC"].push_back(json2);
    }
    json["Monster"] = nullptr;
    if (monster_to_find != nullptr) {
        nlohmann::json json2;
        monster_to_find->Save_character_json_opened(json2);
        json["Monster"].push_back(json2);
    }
    json["Items"] = nullptr;
    if (item_to_find != nullptr) {
        json["Items"].push_back(item_to_find->to_json());
    }
    json["perks"] = nullptr;
    for (const auto &ski: skills_for_task) {
        nlohmann::json skill = ski.toJson();
        json["perks"].push_back(skill);
    }
    return json;
}

void Task::Print(std::ostream &os) const {
    os << Task_name << std::endl;
    os << Task_description << std::endl;
    if (!skills_for_task.empty()) {
        os << "Required perks: \n";
        for (const auto &ski: skills_for_task) {
            os << ski.name << " level: " << ski.level << std::endl;
        }
        os << std::endl;
    }
    os << "your task reward is ";

    os << award << " gold coins";

    if (!prizes.empty()) {
        for (const auto &prize: prizes) {
            os << " and " << prize->Item_name << " ";
        }
    }
    os << endl;
}

bool Task::Get_reward(shared_ptr<Character> &user) {
    if (Finished) {
        user->add_Money(award);
        if (!prizes.empty()) {
            for (auto &prize: prizes) {
                user->Put_in_backpack(prize);
            }
            prizes.clear();
        }
        return true;
    }
    return false;
}

std::vector<shared_ptr<Item>> Task::Get_reward(int &Award) {
    std::vector<shared_ptr<Item>> final_prizes;
    if (Finished) {
        Award = award;
        for (auto &item: prizes) {
            final_prizes.push_back(item);
        }


    }
    return final_prizes;
}