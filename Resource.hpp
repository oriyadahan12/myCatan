#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

enum class Resource {
    Wood,
    Brick,
    Wool,
    Oats,
    Iron,
    Desert
};

std::string resourceToString(Resource resource);

#endif // RESOURCE_H
