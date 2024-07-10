//
// Created by fantomasm on 28.5.23.
//

#include "Item_saver.h"
#include "ItemFactory.h"

bool Item_saver::Add_Item(const std::shared_ptr<Item> &item) {
    if (count_of_items < capacity) {
        items.emplace_back(item);
        sell_value += item->get_sell_value();
        buy_value += item->get_buy_value();
        count_of_items++;
        return true;
    } else {
        // std::cout <<Item_name <<" is full" <<std::endl;
        return false;
    }
}

bool Item_saver::Remove_Item(const std::shared_ptr<Item> &item) {
    for (size_t i = 0; i < items.size(); i++) {
        if (*items[i] == *item) {
            sell_value -= item->get_sell_value();
            buy_value -= item->get_buy_value();
            items.erase(items.begin() + static_cast<int>(i));
            count_of_items--;
            return true;
        }
    }
    return false;
}


void Item_saver::Print(std::ostream &os) {
    os << std::endl;
    Item::Print(os);
    os << "Count of items is " << count_of_items << std::endl;
    os << "Capacity is " << capacity << std::endl;
    os << "Inside of pack :" << std::endl << std::endl;
    for (auto &item: items) {
        item->Print(os);
    }
    os << std::endl;
}


nlohmann::json Item_saver::convertToJson() const {
    nlohmann::json jsonItems;

    for (const auto &item: items) {
        nlohmann::json jsonItem;


        jsonItems.push_back(item->to_json());
    }

    return jsonItems;
}

std::string Item_saver::get_class_name() const {
    return class_name;
}

int Item_saver::get_info() const {
    return static_cast<int>(items.size());
}

nlohmann::json Item_saver::to_json() const {
    nlohmann::json jsonItem = Item::to_json();
    jsonItem["capacity"] = capacity;
    jsonItem["Inside items"] = convertToJson();
    return jsonItem;
}

void Item_saver::from_json(nlohmann::json jsonItem) {

    Item::from_json(jsonItem);
    capacity = jsonItem["capacity"];
    items.reserve(capacity);
    if (!jsonItem["Inside items"].is_null() && !jsonItem["Inside items"].empty()) {
        for (const auto &inv_inside: jsonItem["Inside items"]) {
            std::string className = inv_inside["Class_name"];
            ItemPtr obj = ItemFactory::create(className);
            obj->from_json(inv_inside);
            Add_Item(obj);
        }
    }


}

Item_saver &Item_saver::operator+=(const std::shared_ptr<Item> &item) {
    Add_Item(item);
    return *this;
}

Item_saver &Item_saver::operator+=(const Item &item) {
    Add_Item(std::make_shared<Item>(item));
    return *this;
}

std::shared_ptr<Item> Item_saver::operator-(const Item item) {
    for (auto &item1: items) {
        if (item1->Item_name == item.Item_name) {
            std::shared_ptr<Item> item2 = item1;
            Remove_Item(item1);
            return item2;
        }
    }
    return nullptr;
}