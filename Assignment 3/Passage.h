#ifndef ZOORK_PASSAGE_H
#define ZOORK_PASSAGE_H

#include "Location.h"
#include "NullRoom.h"
#include "Room.h"
#include <memory>

class Passage : public Location {
public:
    static void createBasicPassage(Room* , Room* , const std::string &, bool);

    Passage(const std::string & , const std::string & , Room* , Room* );
    Passage(const std::string & , const std::string & , std::shared_ptr<Command> , Room* , Room* );

    void setFrom(Room* );
    Room* getFrom() const;
    void setTo(Room* );
    Room* getTo() const;

private:
    static std::string oppositeDirection(const std::string &);

    Room* fromRoom;
    Room* toRoom;
};

#endif // ZOORK_PASSAGE_H
