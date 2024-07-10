#include "Resource.hpp"
#include <stdexcept>

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
