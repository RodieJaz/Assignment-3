#include "Room.h"
#include "NullPassage.h"
#include <algorithm>
#include <iostream>
#include <utility>

Room::Room(const std::string &n, const std::string &d) : Location(n, d) {
    enterCommand = std::make_shared<RoomDefaultEnterCommand>(this);
}

Room::Room(const std::string &n, const std::string &d, std::shared_ptr<Command> c) : Location(n, d, std::move(c)) {}

void Room::addPassage(const std::string &direction, std::shared_ptr<Passage> p) {
    passageMap[direction] = std::move(p);
}

void Room::removePassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        passageMap.erase(direction);
    }
}

std::shared_ptr<Passage> Room::getPassage(const std::string &direction) {
    if (passageMap.contains(direction)) {
        return passageMap[direction];
    } else {
        std::cout << "It is impossible to go " << direction << "!\n";
        return std::make_shared<NullPassage>(this);
    }
}

void Room::addItem(std::shared_ptr<Item> item) {
    items.push_back(item);
}

void Room::removeItem(const std::string &itemName) {
    items.erase(std::remove_if(items.begin(), items.end(),
                               [&itemName](const std::shared_ptr<Item> &item) { return item->getName() == itemName; }),
                items.end());
}

std::shared_ptr<Item> Room::getItem(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item->getName() == itemName) {
            return item;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Item>>& Room::getItems() const {
    return items;
}

void Room::showItems() const {
    if (items.empty()) {
        std::cout << "None\n";
    } else {
        for (size_t i = 0; i < items.size(); ++i) {
            std::cout << i + 1 << ". " << items[i]->getName() << "\n";
        }
    }
}
