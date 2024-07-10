//oriyati0701@gmail.com

#include "Resource.hpp"
#include <stdexcept>

/// @brief Converts a Resource enum value to its string representation.
std::string resourceToString(Resource resource) {
    switch (resource) {
        case Resource::Wood: return "Wood";
        case Resource::Brick: return "Brick";
        case Resource::Wool: return "Wool";
        case Resource::Oats: return "Oats";
        case Resource::Iron: return "Iron";
        default: return "Desert";
    }
}

/// @brief Converts an unsigned int to a Resource enum value.
/// @throws std::invalid_argument if the number does not correspond to a valid resource.
Resource intToResource(unsigned int number) {
    switch (number) {
        case 0: return Resource::Wood;
        case 1: return Resource::Brick;
        case 2: return Resource::Wool;
        case 3: return Resource::Oats;
        case 4: return Resource::Iron;
    }
    throw std::invalid_argument("Unsupported resource type");
}
