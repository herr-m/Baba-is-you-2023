/**
    @file Rules.h
    @brief Contains the declaration of the classes related to the rules of the game.
*/
#ifndef RULES_H
#define RULES_H

#include <algorithm>
#include "MapEntity.h"

/**
    @brief The Rule class represents a rule that can be applied to a map.
    A Rule is defined by a subject EntityType and an algorithm
    that can be applied to a vector of MapEntity objects.
*/
class Rule {
protected:
    EntityType _subject;
public:
    /**
        @brief Constructs a new Rule object.
        @param subject The EntityType concerned by the rule.
    */
    Rule(EntityType subject) : _subject(subject) {}

    /**
        @brief Applies the rule to a vector of MapEntity objects.
        This is a pure virtual function, so it must be implemented by any
        subclass of Rule.
        @param map A reference to a vector of MapEntity objects to apply the rule to.
    */
    virtual bool apply(std::vector<MapEntity>& map) = 0;
};

/**
    @class IsStop
    @brief A Rule that stops all other entities on the map when a specific EntityType is encountered.
    @note Inherits from Rule.
*/
class IsStop : public Rule {
public:
    /**
        @brief Constructs an IsStop object with the specified EntityType as the subject.
        @param subject The EntityType that triggers the stop behavior.
    */
    IsStop(EntityType subject) : Rule(subject) {}
    /**
        @brief Applies the stop behavior to the map.
        @param map A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        std::vector<Position> positions;
        auto found{std::begin(map)};
        do {
            found = std::find_if(found+1, std::end(map), [&](const MapEntity& entity) {
                return entity.getType() == _subject;
            });
            if(found != std::end(map))
                positions.push_back(found->getPosition());
        } while(found != std::end(map));

        for(Position p : positions) {
            for(MapEntity& ent : map) {
                if(ent.getPosition() == p && ent.getType() != _subject)
                    ent.move(-ent.getDirection());
            }
        }
        return false;
    }
};

/**
    @class IsPush
    @brief A Rule that moves an entities of a specific type if another entity is trying to push it.
    @note Inherits from Rule.
*/
class IsPush : public Rule {
public:
    /**
        @brief Constructs an IsPush object with the specified EntityType as the subject.
        @param subject The EntityType that triggers the push behavior.
    */
    IsPush(EntityType subject) : Rule(subject) {}
    /**
        @brief Applies the push behavior to the map.
        @param map A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        bool changed{};
        for(MapEntity& entity : map) {
            if(entity.getType() == _subject) {
                auto found = std::find_if(std::begin(map), std::end(map), [&](const MapEntity& ent) {
                    return entity.getPosition() == ent.getPosition() && &entity != &ent && ent.getDirection() != NODIR;
                });
                if(found != std::end(map)) {
                    
                    if(entity.canMove(found->getDirection()) && entity.getDirection() == NODIR) {
                        entity.move(found->getDirection());
                        changed = true;
                    }
                    else 
                        found->move(-found->getDirection());
                }
            }
        }
        return changed;
    };
};

/**
    @class IsKill
    @brief A Rule that destroys entities on the map when they encounter a specific EntityType.
    @note Inherits from Rule.
*/
class IsKill : public Rule {
public:
    /**
        @brief Constructs an IsKill object with the specified EntityType as the subject.
        @param subject The EntityType that triggers the kill behavior.
    */
    IsKill(EntityType subject) : Rule(subject) {}
    /**
        @brief Applies the kill behavior to the map.
        @param map A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        std::vector<Position> positions;
        for(const MapEntity& entity : map)
            if(entity.getType() == _subject)
                positions.push_back(entity.getPosition());

        for(Position pos : positions) {
            std::remove_if(std::begin(map), std::end(map), [&](const MapEntity& entity) {
                return entity.getPosition() == pos && entity.getType() != _subject;
            });
        }
        return false;
    }
};

/**
    @class IsSink
    @brief A Rule with a similar behavior as IsKill that also destroys the subject on trigger.
    @note Inherits from Rule.
*/
class IsSink : public Rule {
public:
    /**
        @brief Constructs an IsSink object with the specified EntityType as the subject.
        @param subject The EntityType that triggers the kill behavior.
    */
    IsSink(EntityType subject) : Rule(subject) {}
    /**
        @brief Applies the sink behavior to the map.
        @param map A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        std::vector<unsigned> positions;
        for(unsigned i=0; i<map.size(); ++i)
            if(map.at(i).getType() == _subject)
                positions.push_back(i);

        std::vector<decltype(std::begin(map))> toRemove{};
        for(unsigned pos : positions) {
            auto found{std::begin(map)};
            do {
                found = std::find_if(found+1, std::end(map), [&](const MapEntity& entity){
                    return entity.getPosition() == map.at(pos).getPosition() && entity.getType() != _subject;
                });
                if(found != std::end(map)) {
                    toRemove.push_back(found);
                    toRemove.push_back(std::begin(map)+pos-1);
                }
            } while(found != std::end(map));
        }
        for(auto x : toRemove)
            map.erase(x);

        return false;
    }
};

/**
    @class IsWin
    @brief A class representing a rule that checks for a winning condition in the game.    @note Inherits from Rule.
*/
class IsWin : public Rule {
    EntityType* _playerEntity;
    bool* _gameOver;
public:
    /**
        @brief Constructor for the IsWin class.
        @param subject EntityType representing the "goal".
        @param playerEntity Pointer to the entity type representing the player.
        @param gameOver Pointer to a boolean flag indicating if the game is over.
    */
    IsWin(EntityType subject, EntityType* playerEntity, bool* gameOver) : Rule(subject), _playerEntity{playerEntity}, _gameOver{gameOver} {}
    /**
        @brief Applies the win behavior to the map.
        @param map A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        for(const MapEntity& player : map) {
            if(player.getType() != *_playerEntity) { continue; }

            auto found{std::find_if(std::begin(map), std::end(map), [&](const MapEntity& entity) {
                return entity.getType() == _subject && entity.getPosition() == player.getPosition();
            })};
            if(found != std::end(map)) { *_gameOver = true; }
        }
        return false;
    }
};

/**
    @class IsYou
    @brief A class representing a rule that sets the entities controlled by the player.
    @note Inherits from Rule.
*/
class IsYou : public Rule {
    EntityType* _playerEntity;
public:
    /**
        @brief Constructor for the IsYou class.
        @param subject EntityType representing the entity to be controlled by the player.
        @param playerEntity Pointer to the entity type representing the player.
    */
    IsYou(EntityType subject, EntityType* playerEntity) : Rule(subject), _playerEntity{playerEntity} {}
    /**
        @brief Sets the player-controlled entity.
        @param map (unused) A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        if(*_playerEntity == _subject) return false;
        *_playerEntity = _subject;
        return true;
    }
};

/**
    @class EntityIsEntity
    @brief A class representing a rule that replaces all entities of a specific type by another.
    @note Inherits from Rule.
*/
class EntityIsEntity : public Rule {
    EntityType _newEntity;
public:
    /**
        @brief Constructor for the EntityIsEntity class.
        @param subject EntityType representing the entity to be replaced.
        @param newEntity EntityType of the new entity.
    */
    EntityIsEntity(EntityType subject, EntityType newEntity) : Rule(subject), _newEntity{newEntity} {}
    /**
        @brief Executes the replacement on the map.
        @param map A vector of MapEntity objects representing the map.
    */
    bool apply(std::vector<MapEntity>& map) override {
        std::for_each(std::begin(map), std::end(map), [&](MapEntity& entity) {
            if(entity.getType() == _subject)
                entity.setType(_newEntity);
        });
        return false;
    }
};

#endif // RULES_H
