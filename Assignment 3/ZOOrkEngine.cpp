#include "ZOOrkEngine.h"
#include "Room.h"
#include <cctype>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>

ZOOrkEngine::ZOOrkEngine(std::shared_ptr<Room> start) {
    player = Player::instance();
    player->setCurrentRoom(start.get());
    player->getCurrentRoom()->enter();
}

void ZOOrkEngine::run() {
    while (!gameOver) {
        std::cout << "> ";

        std::string input;
        std::getline(std::cin, input);

        std::vector<std::string> words = tokenizeString(input);
        std::string command = words[0];
        std::vector<std::string> arguments(words.begin() + 1, words.end());

        if (command == "go") {
            handleGoCommand(arguments);
        } else if ((command == "look") || (command == "inspect")) {
            handleLookCommand(arguments);
        } else if ((command == "take") || (command == "get")) {
            handleTakeCommand(arguments);
        } else if (command == "drop") {
            handleDropCommand(arguments);
        } else if (command == "quit") {
            handleQuitCommand(arguments);
        } else {
            std::cout << "I don't understand that command.\n";
        }
    }
}

void ZOOrkEngine::handleGoCommand(std::vector<std::string> arguments) {
    std::string direction;
    if (arguments[0] == "n" || arguments[0] == "north") {
        direction = "north";
    } else if (arguments[0] == "s" || arguments[0] == "south") {
        direction = "south";
    } else if (arguments[0] == "e" || arguments[0] == "east") {
        direction = "east";
    } else if (arguments[0] == "w" || arguments[0] == "west") {
        direction = "west";
    } else if (arguments[0] == "u" || arguments[0] == "up") {
        direction = "up";
    } else if (arguments[0] == "d" || arguments[0] == "down") {
        direction = "down";
    } else {
        direction = arguments[0];
    }

    Room* currentRoom = player->getCurrentRoom();
    auto passage = currentRoom->getPassage(direction);
    if (passage && passage->getTo()) {
        player->setCurrentRoom(passage->getTo());
        passage->enter();
    } else {
        std::cout << "You can't go that way.\n";
    }
}

void ZOOrkEngine::handleLookCommand(std::vector<std::string> arguments) {
    Room* currentRoom = player->getCurrentRoom();

    if (arguments.empty()) {
        std::cout << currentRoom->getDescription() << "\n";
        const auto& items = currentRoom->getItems();
        std::cout << "You see:\n";
        for (const auto& item : items) {
            std::cout << " - " << item->getName() << "\n";
        }
    } else {
        std::string target = arguments[0];
        auto items = currentRoom->getItems();
        for (const auto& item : items) {
            if (item->getName() == target) {
                std::cout << item->getDescription() << "\n";
                return;
            }
        }
        std::cout << "You don't see any " << target << " here.\n";
    }
}


void ZOOrkEngine::handleTakeCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Take what?\n";
        return;
    }

    std::string itemName = arguments[0];
    Room* currentRoom = player->getCurrentRoom();
    auto item = currentRoom->getItem(itemName);

    if (item) {
        currentRoom->removeItem(itemName);
        player->addItem(item);
        std::cout << "You take the " << itemName << ".\n";
    } else {
        std::cout << "There is no " << itemName << " here.\n";
    }
}

void ZOOrkEngine::handleDropCommand(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        std::cout << "Drop what?\n";
        return;
    }

    std::string itemName = arguments[0];
    auto item = player->getItem(itemName);

    if (item) {
        player->removeItem(itemName);
        player->getCurrentRoom()->addItem(item);
        std::cout << "You drop the " << itemName << ".\n";
    } else {
        std::cout << "You don't have a " << itemName << ".\n";
    }
}



void ZOOrkEngine::handleQuitCommand(std::vector<std::string> arguments) {
    std::string input;
    std::cout << "Are you sure you want to QUIT?\n> ";
    std::cin >> input;
    std::string quitStr = makeLowercase(input);

    if (quitStr == "y" || quitStr == "yes") {
        gameOver = true;
    }
}

std::vector<std::string> ZOOrkEngine::tokenizeString(const std::string &input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ' ')) {
        tokens.push_back(makeLowercase(token));
    }

    return tokens;
}

std::string ZOOrkEngine::makeLowercase(std::string input) {
    std::string output = std::move(input);
    std::transform(output.begin(), output.end(), output.begin(), ::tolower);

    return output;
}
