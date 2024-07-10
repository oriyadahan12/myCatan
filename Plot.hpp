#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include <string>
#include "Resource.hpp"

class Player;

/// Represents a plot of land in the New Catan game, associated with a specific resource type.
class Plot {
public:
    /// @brief Constructs a Plot object with the specified resource type.
    Plot(Resource type);

    /// @brief Gets the resource type of the plot.
    Resource getType() const;

    /// @brief Converts the plot information to a string representation.
    std::string toString() const;

private:
    Resource type; ///< The resource type of the plot.
};

#endif // PLOT_HPP
