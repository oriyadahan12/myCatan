#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>

enum class Resource: unsigned int {
    Wood=0,
    Brick=1,
    Wool=2,
    Oats=3,
    Iron=4,
    None = 999
};

std::string resourceToString(Resource resource);

#endif // RESOURCE_H
