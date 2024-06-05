#ifndef ZOORKENGINE_H
#define ZOORKENGINE_H

#include "Player.h"
#include "Passage.h"
#include "Location.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class ZOOrkEngine {
public:
    explicit ZOOrkEngine(std::shared_ptr<Room> start);

    void run();

private:
    Player* player;
    bool gameOver = false;

    void handleGoCommand(std::vector<std::string> arguments);
    void handleLookCommand(std::vector<std::string> arguments);
    void handleTakeCommand(std::vector<std::string> arguments);
    void handleDropCommand(std::vector<std::string> arguments);
    void handleQuitCommand(std::vector<std::string> arguments);

    std::vector<std::string> tokenizeString(const std::string &input);
    std::string makeLowercase(std::string input);
};

#endif //ZOORKENGINE_H
