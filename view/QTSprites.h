/**
    @file QTSprites.h
    @brief Defines the sprites map, which contains the images for MapEntity objects.
*/

#ifndef QTSPRITES_H
#define QTSPRITES_H

#include <map>
#include <QMovie>
#include "../core/MapEntity.h"

/**
    @brief A map of EntityTypes to their corresponding sprites (images).
    @details Contains the sprites for each EntityType.
*/
static std::map<EntityType, QMovie*> sprites;

/**
    @brief Loads the images from the disk (!!! Must be called AFTER a QApplication is created !!!)
*/
void loadSprites() {
    sprites.insert_or_assign(EntityType::WALL, new QMovie("assets/WALL_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_WALL, new QMovie("assets/Text_WALL_0.gif"));
    sprites.insert_or_assign(EntityType::ROCK, new QMovie("assets/ROCK_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_ROCK, new QMovie("assets/Text_ROCK_0.gif"));
    sprites.insert_or_assign(EntityType::FLAG, new QMovie("assets/FLAG_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_FLAG, new QMovie("assets/Text_FLAG_0.gif"));
    sprites.insert_or_assign(EntityType::METAL, new QMovie("assets/TILE_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_METAL, new QMovie("assets/Text_TILEf"));
    sprites.insert_or_assign(EntityType::GRASS, new QMovie("assets/GRASS_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_GRASS, new QMovie("assets/Text_GRASS_0.gif"));
    sprites.insert_or_assign(EntityType::WATER, new QMovie("assets/WATER_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_WATER, new QMovie("assets/Text_WATER_0.gif"));
    sprites.insert_or_assign(EntityType::LAVA, new QMovie("assets/LAVA_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_LAVA, new QMovie("assets/Text_LAVA_0.gif"));
    sprites.insert_or_assign(EntityType::BABA, new QMovie("assets/BABA_0.gif"));
    sprites.insert_or_assign(EntityType::TEXT_BABA, new QMovie("assets/Text_BABA_0.gif"));
    sprites.insert_or_assign(EntityType::YOU, new QMovie("assets/Prop_YOU.gif"));
    sprites.insert_or_assign(EntityType::STOP, new QMovie("assets/Prop_STOP.gif"));
    sprites.insert_or_assign(EntityType::PUSH, new QMovie("assets/Prop_PUSH.gif"));
    sprites.insert_or_assign(EntityType::WIN, new QMovie("assets/Prop_WIN.gif"));
    sprites.insert_or_assign(EntityType::KILL, new QMovie("assets/Prop_DEFEAT.gif"));
    sprites.insert_or_assign(EntityType::SINK, new QMovie("assets/Prop_SINK.gif"));
    sprites.insert_or_assign(EntityType::IS, new QMovie("assets/Op_IS.gif"));
    sprites.insert_or_assign(EntityType::BEST, new QMovie("assets/Prop_BEST.gif"));
}

#endif // QTSPRITES_H
