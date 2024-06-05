#ifndef ZOORK_ROOM_H
#define ZOORK_ROOM_H

#include "RoomDefaultEnterCommand.h"
#include "Character.h"
#include "Location.h"
#include "Item.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>

class Passage;

class Room : public Location {
public:
    Room(const std::string&, const std::string&);
    Room(const std::string&, const std::string&, std::shared_ptr<Command>);

    void addPassage(const std::string &, std::shared_ptr<Passage>);
    void removePassage(const std::string &);
    std::shared_ptr<Passage> getPassage(const std::string &);

    void addItem(std::shared_ptr<Item> item);
    void removeItem(const std::string& itemName);
    std::shared_ptr<Item> getItem(const std::string&) const;
    const std::vector<std::shared_ptr<Item>>& getItems() const;

    void showItems() const;

private:
    std::map<std::string, std::shared_ptr<Passage>> passageMap;
    std::vector<std::shared_ptr<Item>> items;
};

#endif // ZOORK_ROOM_H
