/**
    @file MapEntity.h
    @brief Defines the MapEntity class and related enums and maps.
*/

#ifndef MAPENTITY_H
#define MAPENTITY_H

#include "Utils.h"
#include <map>
#include <string>
#include <utility>

/**
    @brief Enum for all possible types of entities that can exist on the game map.
*/
enum EntityType{
    ROCK,WALL,FLAG,METAL,GRASS,WATER,LAVA,BABA,
    TEXT_ROCK,TEXT_WALL,TEXT_FLAG,TEXT_METAL,TEXT_GRASS,TEXT_WATER,TEXT_LAVA,TEXT_BABA,
    YOU,STOP,PUSH,WIN,KILL,SINK,
    IS, NONE,
    BEST
};

/**
    @brief Class representing a single entity on the game map.
*/
class MapEntity {
    EntityType _type;
    Position _position;
    Direction _direction;
    std::pair<unsigned, unsigned>* _maxPos;
public:
    /**
        @brief Constructs a new MapEntity object.
        @param type The type of entity.
        @param x The entity's initial X position.
        @param y The entity's initial Y position.
        @param maxPos Pointer to the map dimensions for bound checks.
    */
    MapEntity(EntityType type, unsigned x, unsigned y, std::pair<unsigned, unsigned>* maxPos)
        : _type(type), _position(Position(x, y)), _direction{NODIR}, _maxPos{maxPos} {}
    
    /**
        @brief Checks if the entity can move in a given direction.
        @param direction The direction to check.
        @return true if the entity can move in the given direction, false otherwise.
    */
    bool canMove(Direction direction) {
        Position newPos = _position + direction;
        return newPos.first < _maxPos->first && newPos.second < _maxPos->second && 
            newPos.first >= 0 && newPos.second >= 0;
    }

    /**
        @brief Moves the entity in a given direction.
        @param direction The direction to move in.
    */
    void move(Direction direction) {
        _direction = direction;
        _position = _position + direction;
    }

    void resetDirection() {
        _direction = NODIR;
    }
    /**
        @brief Returns the current position of the entity.
        @return The position of the entity.
    */
    Position getPosition() const { return _position; }

    /**
        @brief Returns the current direction of the entity.
        @return The direction of the entity.
    */
    Direction getDirection() const { return _direction; }

    /**
        @brief Returns the type of the entity.
        @return The type of the entity.
    */
    EntityType getType() const { return _type; }

    /**
        @brief Sets the type of the entity.
        @param type The new type of the entity.
    */
    void setType(EntityType type) { _type = type; }
};

/**
    @brief A map used for translating strings to EntityType values
*/
static const std::map<std::string, EntityType> stringToEntityType {
    {"rock", ROCK},     {"text_rock", TEXT_ROCK},
    {"wall", WALL},     {"text_wall", TEXT_WALL},
    {"flag", FLAG},     {"text_flag", TEXT_FLAG},
    {"metal", METAL},   {"text_metal", TEXT_METAL},
    {"grass", GRASS},   {"text_grass", TEXT_GRASS},
    {"water", WATER},   {"text_water", TEXT_WATER},
    {"lava", LAVA},     {"text_lava", TEXT_LAVA},
    {"baba", BABA},     {"text_baba", TEXT_BABA},
    {"you", YOU},
    {"stop", STOP},
    {"push", PUSH},
    {"win", WIN},
    {"kill", KILL},
    {"sink", SINK},
    {"is", IS},
    {"text_best", BEST}
};

/**
    @brief A map used for translating EntityType values to strings
*/
static const std::map<EntityType, std::string> entityTypeToString {
    {ROCK, "rock"},     {TEXT_ROCK, "text_rock"},
    {WALL, "wall"},     {TEXT_WALL, "text_wall"},
    {FLAG, "flag"},     {TEXT_FLAG, "text_flag"},
    {METAL, "metal"},   {TEXT_METAL, "text_metal"},
    {GRASS, "grass"},   {TEXT_GRASS, "text_grass"},
    {WATER, "water"},   {TEXT_WATER, "text_water"},
    {LAVA, "lava"},     {TEXT_LAVA, "text_lava"},
    {BABA, "baba"},     {TEXT_BABA, "text_baba"},
    {YOU, "you"},
    {STOP, "stop"},
    {PUSH, "push"},
    {WIN, "win"},
    {KILL, "kill"},
    {SINK, "sink"},
    {IS, "is"},
    {BEST, "text_best"}
};

/**
    @brief A map used for translating text entities to their concrete counterparts
*/
static const std::map<EntityType, EntityType> textEntToRealEnt {
    {TEXT_ROCK, ROCK},
    {TEXT_WALL, WALL},
    {TEXT_FLAG, FLAG},
    {TEXT_METAL, METAL},
    {TEXT_GRASS, GRASS},
    {TEXT_WATER, WATER},
    {TEXT_LAVA, LAVA},
    {TEXT_BABA, BABA}
};

/**
    @brief A map used for translating text entities to their concrete counterparts including rule components
*/
static const std::map<EntityType, EntityType> textEntToRule {
    {TEXT_ROCK, ROCK},
    {TEXT_WALL, WALL},
    {TEXT_FLAG, FLAG},
    {TEXT_METAL, METAL},
    {TEXT_GRASS, GRASS},
    {TEXT_WATER, WATER},
    {TEXT_LAVA, LAVA},
    {TEXT_BABA, BABA},
    {YOU, YOU},
    {STOP, STOP},
    {PUSH, PUSH},
    {WIN, WIN},
    {KILL, KILL},
    {SINK, SINK},
    {IS, IS}
};

#endif // MAPENTITY_H
