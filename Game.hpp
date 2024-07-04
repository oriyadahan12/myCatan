#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include "Player.hpp"
#include "Plot.hpp"

class Game {
public:
    int numPlayers = 0;
    Game();
    void initializeBoard();
    void addPlayer(const std::string& name);
    Player& getPlayer(int index);
    void printBoard() const;
    void printPlayers();
    void rollDiceAndDistributeResources();

    // Methods for placing settlements and cities
    void placeSettlement(int playerIndex, int plotIndex);
    void placeCity(int playerIndex, int plotIndex);

    // Additional methods for interactive gameplay
    void printAvailablePlots() const; // Print available plots for settlement
    bool isValidPlotIndex(int plotIndex) const; // Check if plot index is valid

    int getBoardSize();

private:
    std::vector<Player> players;
    std::vector<Plot> boardPlots;
    std::mt19937 rng;

    int rollDice();

};

#endif // GAME_H
