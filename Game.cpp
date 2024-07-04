#include "Game.hpp"
#include <iostream>
#include <random>

int numPlayers = 0;
Game::Game() : rng(std::random_device()()) {
    initializeBoard();
}

void Game::initializeBoard() {
    boardPlots = {
            Plot(Plot::Type::Forest, 5), Plot(Plot::Type::Hills, 2), Plot(Plot::Type::Pasture, 6),
            Plot(Plot::Type::Agricultural, 3), Plot(Plot::Type::Mountains, 8), Plot(Plot::Type::Forest, 10),
            Plot(Plot::Type::Hills, 9), Plot(Plot::Type::Pasture, 12), Plot(Plot::Type::Agricultural, 11),
            Plot(Plot::Type::Mountains, 4), Plot(Plot::Type::Forest, 8), Plot(Plot::Type::Hills, 10),
            Plot(Plot::Type::Pasture, 9), Plot(Plot::Type::Agricultural, 4), Plot(Plot::Type::Mountains, 5),
            Plot(Plot::Type::Forest, 6), Plot(Plot::Type::Hills, 11), Plot(Plot::Type::Pasture, 3),
            Plot(Plot::Type::Desert, 7)
    };
}

void Game::addPlayer(const std::string& name) {
    players.emplace_back(name);
}

Player& Game::getPlayer(int index) {
    return players.at(index);
}

void Game::printBoard() const {
    std::cout << "Game Board:" << std::endl;
    for (size_t i = 0; i < boardPlots.size(); ++i) {
        std::cout << "Plot " << i + 1 << ": Resource - " << static_cast<int>(boardPlots[i].getResourceType())
                  << ", Number - " << boardPlots[i].getNumber() << std::endl;
    }
}

void Game::printPlayers() {
    std::cout << "Players:" << std::endl;
    for (const auto& player : players) {
        numPlayers++;
        std::cout << player.getName() << std::endl;
    }
}

int getNumPlayers()  {
    return numPlayers;
}
int Game::rollDice() {
    std::uniform_int_distribution<int> dist(1, 6); // Distribution for a six-sided die
    return dist(rng) + dist(rng); // Roll two dice and return the sum
}

void Game::rollDiceAndDistributeResources() {
    int rollResult = rollDice();
    std::cout << "Dice roll: " << rollResult << std::endl;

    for (auto& plot : boardPlots) {
        if (plot.getNumber() == rollResult) {
            for (auto* player : plot.getAdjacentSettlements()) {
                player->addResource(plot.getResourceType(), 1);
            }
            for (auto* player : plot.getAdjacentCities()) {
                player->addResource(plot.getResourceType(), 2);
            }
        }
    }
}

void Game::placeSettlement(int playerIndex, int plotIndex) {
    if (playerIndex < players.size() && plotIndex < boardPlots.size()) {
        players[playerIndex].addSettlement(boardPlots[plotIndex]);
    }
}

void Game::placeCity(int playerIndex, int plotIndex) {
    if (playerIndex < players.size() && plotIndex < boardPlots.size()) {
        players[playerIndex].upgradeSettlementToCity(boardPlots[plotIndex]);
    }
}

void Game::printAvailablePlots() const {
    std::cout << "Available Plots:" << std::endl;
    for (size_t i = 0; i < boardPlots.size(); ++i) {
        if (!boardPlots[i].isOccupied()) {
            std::cout << "Plot " << i + 1 << ": Resource - " << static_cast<int>(boardPlots[i].getResourceType())
                      << ", Number - " << boardPlots[i].getNumber() << std::endl;
        }
    }
}


bool Game::isValidPlotIndex(int plotIndex) const {
    return plotIndex >= 0 && plotIndex < boardPlots.size() && !boardPlots[plotIndex].isOccupied();
}

int Game::getBoardSize() {
    return 22;
}
