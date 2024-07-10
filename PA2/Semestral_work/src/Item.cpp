//
// Created by fantomasm on 4.5.23.
//

#include "Item.h"

bool Item::operator==(const Item &it) const {
    if (Item_name == it.Item_name) {
        return true;
    }
    return false;
}

Item::Item() : Item_name("None"), buy_value(0), sell_value(0) {}

Item::~Item() {
    Item_name.clear();
}

//+= and - operator are created more for item_saver or to combine items, for example to put values into one Item
Item &Item::operator+=(const Item &item) {
    buy_value += item.buy_value;
    sell_value += item.sell_value;
    return *this;
}

std::shared_ptr<Item> Item::operator-(const Item item) {
    buy_value -= item.buy_value;
    sell_value -= item.sell_value;
    return std::make_shared<Item>(*this);
}

//trivial Print method
void Item::Print(std::ostream &os) {

    os << Item_name << std::endl;
    os << "Buy value is " << buy_value << std::endl;
    os << "Sell value is " << sell_value << std::endl;
}

//trivial method to convert Item to json format
nlohmann::json Item::to_json() const {
    nlohmann::json jsonItem;
    jsonItem["Class_name"] = get_class_name();
    jsonItem["Item_name"] = Item_name;
    jsonItem["buy_value"] = buy_value;
    jsonItem["sell_value"] = sell_value;
    return jsonItem;
}

//same for converting from json
void Item::from_json(nlohmann::json jsonItem) {

    Item_name = jsonItem["Item_name"];
    buy_value = jsonItem["buy_value"];
    sell_value = jsonItem["sell_value"];

}


Item &Item::operator+=(const std::shared_ptr<Item> &item) {
    buy_value -= item->buy_value;
    sell_value -= item->sell_value;
    return *this;
}
