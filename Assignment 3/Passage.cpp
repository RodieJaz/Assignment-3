#include "Passage.h"

#include "PassageDefaultEnterCommand.h"
#include <utility>

std::string Passage::oppositeDirection(const std::string& direction) {
    if (direction == "north") return "south";
    else if (direction == "south") return "north";
    else if (direction == "east") return "west";
    else if (direction == "west") return "east";
    else return "unknown_direction";
}

void Passage::createBasicPassage(Room* from, Room* to, const std::string& direction, bool bidirectional = true) {
    std::string passageName = from->getName() + "_to_" + to->getName();
    auto temp1 = std::make_shared<Passage>(passageName, "A totally normal passageway.", from, to);
    from->addPassage(direction, temp1);
    if (bidirectional) {
        std::string passageName2 = to->getName() + "_to_" + from->getName();
        auto temp2 = std::make_shared<Passage>(passageName2, "A totally normal passageway.", to, from);
        to->addPassage(oppositeDirection(direction), temp2);
    }
}

Passage::Passage(const std::string& n, const std::string& d, Room* from, Room* to)
    : Location(n, d), fromRoom(from), toRoom(to) {
    setEnterCommand(std::make_shared<PassageDefaultEnterCommand>(this));
}

Passage::Passage(const std::string& n, const std::string& d, std::shared_ptr<Command> c, Room* from, Room* to)
    : Location(n, d, std::move(c)), fromRoom(from), toRoom(to) {}

void Passage::setFrom(Room* r) {
    fromRoom = r;
}

Room* Passage::getFrom() const {
    return fromRoom;
}

void Passage::setTo(Room* r) {
    toRoom = r;
}

Room* Passage::getTo() const {
    return toRoom;
}