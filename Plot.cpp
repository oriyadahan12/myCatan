#include <iostream>
#include "Plot.hpp"

Plot::Plot(Resource t) : type(t) {/* std::cout << resourceToString(t) << std::endl;  */}

Resource Plot::getType() const {
    return type;
}

std::string Plot::toString() const {
    return resourceToString(type);
}

