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
    Player(const std::string& name);

    void addResource(Resource resource, unsigned int amount);
    void removeResource(Resource resource, unsigned  int amount);
    unsigned int getResourceCount(Resource resource) const;

    void printResources() const;
    void printCards() const;

    bool canAfford(std::map<Resource, unsigned int> price) const;
    void pay(std::map<Resource, unsigned int> price);
    void receive(std::map<Resource, unsigned int> price);

    unsigned int getVictoryPoints() const;
    unsigned int sumResources() const;
    void loseHalfResources();
    void loseResource(Resource);

    void addVictoryPoint(unsigned int amount) { victoryPoints += amount; }

    void addDevelopmentCard(DevelopmentCard* card);
    void playDevelopmentCard(string str, Game&);
    unsigned int numCards() const { return developmentCards.size(); }
    unsigned int numCards(string) const;
    void removeCard(string);

    std::string getName() const;


private:
    std::string name;
    std::map<Resource, unsigned int> resources;
    std::map<DevelopmentCard*, unsigned int> developmentCards;
    unsigned int victoryPoints;

};

#endif // PLAYER_HPP
