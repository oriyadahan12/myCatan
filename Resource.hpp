#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

/// @brief Enumeration of the different types of resources in the New Catan game.
enum class Resource : unsigned int {
    Wood = 0,   ///< Wood resource.
    Brick = 1,  ///< Brick resource.
    Wool = 2,   ///< Wool resource.
    Oats = 3,   ///< Oats resource.
    Iron = 4,   ///< Iron resource.
    None = 999  ///< No resource.
};

/// @brief Converts a Resource enum value to its string representation.
std::string resourceToString(Resource resource);

/// @brief Converts an unsigned int to a Resource enum value.
Resource intToResource(unsigned int value);

#endif // RESOURCE_H
