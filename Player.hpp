#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Plot.hpp" // Include Plot class definition

\
class DevelopmentCard {
public:
    enum class Type {
        Knight,
        VictoryPoint,
        Promotion
    };

    enum class PromotionType {
        Monopoly,
        RoadBuilding,
        YearOfPlenty
    };

    DevelopmentCard(Type type, PromotionType promoType = PromotionType::Monopoly)
            : type(type), promoType(promoType) {}

    Type getType() const { return type; }
    PromotionType getPromotionType() const { return promoType; }

private:
    Type type;
    PromotionType promoType;
};

class Player {
public:
    Player(const std::string& name);

    void addResource(Resource resource, int amount);
    void removeResource(Resource resource, int amount);
    int getResourceCount(Resource resource) const;

    void addSettlement(Plot& plot);
    void upgradeSettlementToCity(Plot& plot);
    void addRoad();
    bool canBuildRoad() const;
    bool canBuildSettlement(Plot& plot) const;
    bool canBuildCity(Plot& plot) const;

    int getVictoryPoints() const;

    void addDevelopmentCard(const DevelopmentCard& card);
    void useDevelopmentCard(int index);
    void playDevelopmentCard(int index, Player& target);

    void initiateTrade(Player& otherPlayer,
                       const std::map<Resource, int>& offer,
                       const std::map<Resource, int>& request,
                       std::function<void(bool)> callback);

    void respondToTrade(Player& initiator,
                        const std::map<Resource, int>& offer,
                        const std::map<Resource, int>& request,
                        std::function<void(bool)> callback);

    std::vector<DevelopmentCard> getDevelopmentCards() const;
    std::string getName() const;
    void chooseInitialPlots(std::vector<Plot*>& availablePlots); // New method for initial plot selection
    void printSettlements() const;

private:
    std::string name;
    std::map<Resource, int> resources;
    std::vector<DevelopmentCard> developmentCards;
    std::vector<Plot*> ownedPlots;
    int settlements;
    int cities;
    int roads;
    int victoryPoints;

    void calculateVictoryPoints();
};

#endif // PLAYER_HPP
