#include "Item.h"
#include <iostream>

Item::Item()
    : name(""), description(""), value(0), effectValue(0), type(ItemType::None), hidden(false) {}

Item::Item(const std::string& name, const std::string& description,
           int value, int effectValue, ItemType type, bool hidden)
    : name(name), description(description),
      value(value), effectValue(effectValue), type(type), hidden(hidden) {}

std::string Item::getName()        const { return name; }
std::string Item::getDescription() const { return description; }
int         Item::getValue()       const { return value; }
int         Item::getEffectValue() const { return effectValue; }
ItemType    Item::getType()        const { return type; }
bool        Item::isHidden()       const { return hidden; }

void Item::print() const {
    std::string typeStr;
    switch (type) {
        case ItemType::Weapon: typeStr = "무기";   break;
        case ItemType::Food:   typeStr = "음식";   break;
        case ItemType::Pet:    typeStr = "펫";     break;
        case ItemType::Goods:  typeStr = "상품";   break;
        default:               typeStr = "기타";   break;
    }
    std::cout << "[" << typeStr << "] " << name
              << " (가격: " << value << "원"
              << ", 효과치: " << effectValue << ") - "
              << description << "\n";
}
