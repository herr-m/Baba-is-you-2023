/**
    @file Core.h
    @brief Defines the Core class for managing the game logic.
*/

#ifndef CORE_H
#define CORE_H

#include <vector>
#include <string>
#include <memory>
#include "MapEntity.h"
#include "Rules.h"
#include "Map.h"
#include "../utils/subject.h"

/**
    @brief The Core class manages the game logic and state.
*/
class Core : public nvs::Subject {
    Map _map;
    Map _initialMap;
    const std::map<std::pair<EntityType, EntityType>, std::shared_ptr<Rule>> _allRules;
    const std::vector<std::shared_ptr<Rule>> _permanentRules;
    std::vector<std::shared_ptr<Rule>> _rules;
    EntityType _playerEntity;
    bool _gameOver;

    std::map<std::pair<EntityType, EntityType>, std::shared_ptr<Rule>> getAllRules();
    void movePlayer(Direction direction);
    void resetMap();
    void resetEntities();
    void updateRules();
    void applyPermanentRules();
    void applyRules();
public:
    /**
        @brief Constructs a new Core object with the game map loaded from the specified file.
        @param filePath The path of the file containing the game map.
    */
    Core(const std::string& filePath);

    /**
        @brief Gets the current game map.
        @return The current game map.
    */
    const Map& getMap() const;

    /**
        @brief Checks whether the game is over.
        @return true if the game is over, false otherwise.
    */
    bool isGameOver() const;
    
    /**
        @brief Manages the user input.
        @param input The user input.
    */
    void manageInput(UserInput input);

    /**
        @brief Updates the game state and notifies the view.
    */
    void update();
};

#endif // CORE_H
