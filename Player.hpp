#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Plot.hpp" // Include Plot class definition
#include "development_card.hpp"

class Player {
public:
    Player(const std::string& name);

    void addResource(Resource resource, unsigned int amount);
    void removeResource(Resource resource, int amount);
    int getResourceCount(Resource resource) const;

    bool canAfford(std::map<Resource, unsigned int> price) const;
    void pay(std::map<Resource, unsigned int> price);
    void receive(std::map<Resource, unsigned int> price);

    int getVictoryPoints() const;
    int sumResources() const;
    void loseHalfResources();

//    void addDevelopmentCard(const DevelopmentCard& card);
//    void useDevelopmentCard(int index);
//    void playDevelopmentCard(int index, Player& target);
//
//    void initiateTrade(Player& otherPlayer,
//                       const std::map<Resource, int>& offer,
//                       const std::map<Resource, int>& request,
//                       std::function<void(bool)> callback);
//
//    void respondToTrade(Player& initiator,
//                        const std::map<Resource, int>& offer,
//                        const std::map<Resource, int>& request,
//                        std::function<void(bool)> callback);

    std::string getName() const;


private:
    std::string name;
    std::map<Resource, int> resources;
    std::vector<DevelopmentCard> developmentCards;
    std::vector<Plot*> ownedPlots;
    int victoryPoints;

};

#endif // PLAYER_HPP
