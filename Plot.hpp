#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include <string>
#include "Resource.hpp"

class Player; // Forward declaration

class Plot {
public:

    Plot(Resource type);

    Resource getType() const;
    std::string toString() const;


private:
    Resource type;

};

#endif // PLOT_HPP
