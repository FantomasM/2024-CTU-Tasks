//
// Created by fantomasm on 28.5.23.
//

#ifndef SEMESTRAL_WORK_ITEM_SAVER_H
#define SEMESTRAL_WORK_ITEM_SAVER_H

#include "Item.h"

class Item_saver : public Item {
public:
    inline Item_saver(const std::string &name, int Buy_value, int Sell_value, int Capacity) : Item(name, Buy_value,
                                                                                                   Sell_value),
                                                                                              capacity(Capacity),
                                                                                              count_of_items(0) {
        items.reserve(Capacity);
    }

    Item_saver() = default;

    bool IsItemSaver() const override { return true; }

    bool Add_Item(const std::shared_ptr<Item> &item);

    bool Remove_Item(const std::shared_ptr<Item> &item);

    void Print(std::ostream &os) override;

    const std::string class_name = "Item_saver";

    Item_saver &operator+=(const Item &item) override;

    Item_saver &operator+=(const std::shared_ptr<Item> &item) override;

    std::shared_ptr<Item> operator-(Item item) override;

    std::string get_class_name() const override;

    int get_info() const override;

    nlohmann::json to_json() const override;

    nlohmann::json convertToJson() const;

    void from_json(nlohmann::json jsonItem) override;

private:
    int capacity = 0;
    int count_of_items = 0;
    std::vector<std::shared_ptr<Item>> items;
};

#endif //SEMESTRAL_WORK_ITEM_SAVER_H
