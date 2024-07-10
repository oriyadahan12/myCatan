//oriyati0701@gmail.com

#include <iostream>
#include "Plot.hpp"


Plot::Plot(Resource t) : type(t) {
    std::cout << resourceToString(t) << std::endl;
}

/// @brief Gets the resource type of the plot.
Resource Plot::getType() const {
    return type;
}

/// @brief Converts the plot information to a string representation.
std::string Plot::toString() const {
    return resourceToString(type);
}
