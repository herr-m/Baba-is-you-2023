/**
    @file utils.h
    @brief This file defines some utility types and constants for the game.
*/
#ifndef UTILS_H
#define UTILS_H

#include <utility>

/**
    @typedef Direction
    @brief A pair of short integers representing a direction in the game.
*/
using Direction = std::pair<short, short>;
constexpr Direction UP{-1, 0};
constexpr Direction DOWN{1, 0};
constexpr Direction LEFT{0, -1};
constexpr Direction RIGHT{0, 1};
constexpr Direction NODIR{0, 0};

/**
    @typedef Position
    @brief A pair of unsigned integers representing a position on the game's map.
*/
using Position = std::pair<unsigned, unsigned>;

/**
    @brief Overloads the equality operator for the Position type.
    @param lhs The left-hand side of the operator.
    @param rhs The right-hand side of the operator.
    @return Whether the two positions are equal.
*/
constexpr bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

/**
    @brief Overloads the negation operator for the Position type.
    @param p The position to negate.
    @return The negated position.
*/
constexpr Position operator-(const Position& p) {
    return Position{-p.first, -p.second};
}

/**
    @brief Overloads the addition operator for the Position and Direction types.
    @param pos The position to add the direction to.
    @param dir The direction to add to the position.
    @return The resulting position after adding the direction.
*/
constexpr Position operator+(Position pos, Direction dir) {
    return Position{pos.first + dir.first, pos.second + dir.second};
}

/**
    @enum UserInput
    @brief An enumeration representing the possible user inputs for the game.
*/
enum class UserInput {
    UP, DOWN, LEFT, RIGHT,
    RESET, SAVE, QUIT,
    NONE
};
#endif // UTILS_H
