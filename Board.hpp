#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <string>
#include "Plot.hpp"
#include "Player.hpp" // Include Player class for reference
#include "Village.hpp"
#include "Road.hpp"

class Board {
public:
    Board(); // Constructor with parameters

    void initializePlots(); // Initialization method for the plots
    void produce(unsigned int diceNum);

    void buildRoad(Player& player, unsigned int roadIndex);
    void buildVillage(Player& player, unsigned int villageIndex, bool first = false);
    void upgradeVillage(Player& player, unsigned int villageIndex);

    bool canBuildRoad(Player& player, unsigned int roadIndex) const;
    bool canBuildFirstVillage(Player& player, unsigned int villageIndex) const;
    bool canBuildVillage(Player& player, unsigned int villageIndex) const;
    bool canUpgradeVillage(Player& player, unsigned int villageIndex) const;

    std::string toString() const;


private:
    std::vector<Plot> plots;
    std::vector<Road> roads;
    std::vector<Village> villages;
};

#endif // BOARD_HPP
