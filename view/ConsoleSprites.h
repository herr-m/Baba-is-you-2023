/**
    @file ConsoleSprite.h
    @brief Defines the Sprite struct, which represents the visual representation of a MapEntity.
*/

#ifndef SPRITES_H
#define SPRITES_H

#include <map>
#include <vector>
#include <string>
#include "../core/MapEntity.h"

/**
    @struct Sprite
    @brief A struct representing the visual representation of a MapEntity.
    @details Contains the image, color, foreground color (fg), and background color (bg) of the Sprite.
*/
struct Sprite {
    std::vector<std::string> image;
    int color;
    int fg, bg;
};

/**
    @brief A map of EntityTypes to their corresponding Sprites.
    @details Contains the Sprites for each EntityType.
*/
static const std::map<EntityType, Sprite> sprites {
    {EntityType::WALL, {{"###", "###"}, 1, 0, 8}},
    {EntityType::TEXT_WALL, {{"WA ", " LL"}, 2, 8, 0}},
    {EntityType::ROCK, {{" R ", "R R"}, 3, 0, 3}},
    {EntityType::TEXT_ROCK, {{"RO ", " CK"}, 4, 3, 0}},
    {EntityType::FLAG, {{"<#|", "  |"}, 5, 3, 0}},
    {EntityType::TEXT_FLAG, {{"FL ", " AG"}, 6, 3, 0}},
    {EntityType::METAL, {{"###", "###"}, 7, 8, 0}},
    {EntityType::TEXT_METAL, {{"MET", " AL"}, 8, 8, 0}},
    {EntityType::GRASS, {{" , ", "\" \""}, 9, 2, 0}},
    {EntityType::TEXT_GRASS, {{"GRA", " SS"}, 10, 2, 0}},
    {EntityType::WATER, {{"~ ~", " ~ "}, 11, 7, 4}},
    {EntityType::TEXT_WATER, {{"WAT", " ER"}, 12, 4, 0}},
    {EntityType::LAVA, {{" ~ ", "~ ~"}, 13, 3, 1}},
    {EntityType::TEXT_LAVA, {{"LA ", " VA"}, 14, 1, 0}},
    {EntityType::BABA, {{" @ ", " T "}, 15, 7, 0}},
    {EntityType::TEXT_BABA, {{"BA ", " BA"}, 16, 7, 0}},
    {EntityType::YOU, {{"YOU", "   "}, 17, 0, 5}},
    {EntityType::STOP, {{"ST ", " OP"}, 18, 0, 5}},
    {EntityType::PUSH, {{"PU ", " SH"}, 19, 0, 2}},
    {EntityType::WIN, {{"WIN", "   "}, 20, 0, 3}},
    {EntityType::KILL, {{"KI ", " LL"}, 21, 0, 1}},
    {EntityType::SINK, {{"SI ", " NK"}, 22, 0, 4}},
    {EntityType::IS, {{" I ", " S "}, 23, 7, 0}},
    {EntityType::BEST, {{"BE ", " ST"}, 20, 0, 3}},
};

#endif // SPRITES_H
