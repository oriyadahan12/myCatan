#include "Plot.hpp"

// Constructor initializes the plot type, number, and owner
Plot::Plot(Type type, int number) : type(type), number(number), owner(nullptr) {}

// Returns the plot type
Plot::Type Plot::getType() const {
    return type;
}

// Returns the plot number
int Plot::getNumber() const {
    return number;
}

// Maps plot types to resource types
Resource Plot::getResourceType() const {
    switch (type) {
        case Type::Forest: return Resource::Wood;
        case Type::Hills: return Resource::Brick;
        case Type::Pasture: return Resource::Wool;
        case Type::Agricultural: return Resource::Oats;
        case Type::Mountains: return Resource::Iron;
        case Type::Desert: return Resource::Desert;
        default: return Resource::Desert;
    }
}

// Sets the owner of the plot
void Plot::setOwner(Player* player) {
    owner = player;
}

// Adds a player to the list of adjacent settlements
void Plot::addAdjacentSettlement(Player* player) {
    adjacentSettlements.push_back(player);
}

// Adds a player to the list of adjacent cities
void Plot::addAdjacentCity(Player* player) {
    adjacentCities.push_back(player);
}

// Returns the list of adjacent settlements
const std::vector<Player*>& Plot::getAdjacentSettlements() const {
    return adjacentSettlements;
}

// Returns the list of adjacent cities
const std::vector<Player*>& Plot::getAdjacentCities() const {
    return adjacentCities;
}

// Checks if the plot is occupied by a player
bool Plot::isOccupied() const {
    return owner != nullptr;
}
