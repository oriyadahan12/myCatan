#ifndef PLOT_HPP
#define PLOT_HPP

#include <vector>
#include "Resource.hpp"

class Player; // Forward declaration

class Plot {
public:
    enum class Type {
        Forest,
        Hills,
        Pasture,
        Agricultural,
        Mountains,
        Desert
    };

    Plot(Type type, int number);

    Type getType() const;
    int getNumber() const;
    Resource getResourceType() const;
    void setOwner(Player* player);
    void addAdjacentSettlement(Player* player);
    void addAdjacentCity(Player* player);

    const std::vector<Player*>& getAdjacentSettlements() const;
    const std::vector<Player*>& getAdjacentCities() const;

    bool isOccupied() const; // New method to check if plot is occupied

private:
    Type type;
    int number;
    Player* owner;
    std::vector<Player*> adjacentSettlements;
    std::vector<Player*> adjacentCities;
};

#endif // PLOT_HPP
