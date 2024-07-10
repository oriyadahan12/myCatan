#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Plot.hpp"
#include "development_card.hpp"

class Player {
    public:
    /// @brief Constructs a Player object with the specified name.
    Player(const std::string& name);

    /// @brief Adds a specified amount of a resource to the player's inventory.
    void addResource(Resource resource, unsigned int amount);

    /// @brief Gets the count of a specified resource in the player's inventory.
    unsigned int getResourceCount(Resource resource) const;

    /// @brief Prints the player's resources to the console.
    void printResources() const;

    /// @brief Prints the player's development cards to the console.
    void printCards() const;

    /// @brief Checks if the player can afford a specified price in resources.
    bool canAfford(std::map<Resource, unsigned int> price) const;

    /// @brief Deducts a specified price in resources from the player's inventory.
    void pay(std::map<Resource, unsigned int> price);

    /// @brief Adds a specified price in resources to the player's inventory.
    void receive(std::map<Resource, unsigned int> price);

    /// @brief Gets the player's total victory points.
    unsigned int getVictoryPoints() const;

    /// @brief Sums the total amount of resources in the player's inventory.
    unsigned int sumResources() const;

    /// @brief Makes the player lose half of their resources.
    void loseHalfResources();

    /// @brief Makes the player lose a specified amount of a resource.
    void loseResource(Resource resource, unsigned int amount);

    /// @brief Adds a specified amount of victory points to the player.
    void addVictoryPoint(unsigned int amount) { victoryPoints += amount; }

    /// @brief Adds a development card to the player's inventory.
    void addDevelopmentCard(std::string card);

    /// @brief Plays a development card..
    void playDevelopmentCard(std::string card, Game& game);

    /// @brief Gets the number of a specified development card in the player's inventory.
    unsigned int numCards(std::string card) const;

    /// @brief Removes a specified development card from the player's inventory.
    void removeCard(std::string card);

    /// @brief Gets the player's name.
    std::string getName() const;

private:
    std::string name; ///< The name of the player.
    std::map<Resource, unsigned int> resources; ///< The player's resources.
    std::map<std::string, unsigned int> developmentCards; ///< The player's development cards.
    unsigned int victoryPoints; ///< The player's victory points.
};

#endif // PLAYER_HPP
