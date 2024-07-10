//oriyati0701@gmail.com

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
    /**
     * @brief Constructs a Board object.
     */
    Board();

    /**
     * @brief Initializes the plots on the board.
     */
    void initializePlots();

    /**
     * @brief Simulates resource production based on a dice roll..
     */
    void produce(unsigned int diceNum);

    /**
     * @brief Allows a player to build a road on the specified road index.
     */
    void buildRoad(Player& player, unsigned int roadIndex);

    /**
     * @brief Allows a player to build a village on the specified village index.
     */
    void buildVillage(Player& player, unsigned int villageIndex, bool first = false);

    /**
     * @brief Allows a player to upgrade a village to a city on the specified village index.
     */
    void upgradeVillage(Player& player, unsigned int villageIndex);

    /**
     * @brief Checks if a player can build a road on the specified road index.
     */
    bool canBuildRoad(Player& player, unsigned int roadIndex) const;

    /**
     * @brief Checks if a player can build their first village on the specified village index.
     */
    bool canBuildFirstVillage(Player& player, unsigned int villageIndex) const;

    /**
     * @brief Checks if a player can build a village on the specified village index.
     */
    bool canBuildVillage(Player& player, unsigned int villageIndex) const;

    /**
     * @brief Checks if a player can upgrade a village to a city on the specified village index.
     */
    bool canUpgradeVillage(Player& player, unsigned int villageIndex) const;

    /**
     * @brief Checks if there is a road built at the specified index.
     */
    bool isThereRoad(unsigned int index) const { return roads[index].isBuilt(); }

    /**
     * @brief Checks if there is a village built at the specified index.
     */
    bool isThereVillage(unsigned int index) const { return villages[index].isbuilt(); }

    /**
     * @brief Converts the board state to a string representation.
     */
    std::string toString() const;

private:
    std::vector<Plot> plots;    ///< Vector of plots on the board.
    std::vector<Road> roads;    ///< Vector of roads on the board.
    std::vector<Village> villages; ///< Vector of villages on the board.
};

#endif // BOARD_HPP
