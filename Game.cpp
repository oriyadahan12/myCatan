#include "Game.hpp"
#include <iostream>
#include <random>

Game::Game(string name1, string name2, string name3) : rng(std::random_device()()), board() {
    players.emplace_back(name1);
    players.emplace_back(name2);
    players.emplace_back(name3);
}

Player& Game::getPlayer(unsigned int index) {
    return players.at(index);
}

void Game::printBoard() const {
    std::cout << "Game Board:" << std::endl;
    std::cout << board.toString() << std::endl;
}

void Game::printPlayers() {
    std::cout << "Players:" << std::endl;
    for (const auto& player : players) {
        std::cout << player.getName() << std::endl;
    }
}

unsigned int Game::rollDice() {
    std::uniform_int_distribution<unsigned int> dist(1, 6); // Distribution for a six-sided die
    return dist(rng) + dist(rng); // Roll two dice and return the sum
}

void Game::rollDiceAndProcessResult() {
    unsigned int rollResult = rollDice();
    std::cout << "Dice roll: " << rollResult << std::endl;

    if (rollResult != 7) {
        board.produce(rollResult);
    } else {
        stealResources();
    }
}

void Game::placeSettlement(unsigned int playerIndex,unsigned int plotIndex) {
    if (!players[playerIndex].canAfford(priceVillage))
        throw logic_error("Player can't afford village");
    if (!board.canBuildVillage(players[playerIndex], plotIndex))
        throw logic_error("Player can't place village there");

    players[playerIndex].pay(priceVillage);
    board.buildVillage(players[playerIndex], plotIndex);
}

void Game::placeRoad(unsigned int playerIndex, unsigned int plotIndex) {
    if (!players[playerIndex].canAfford(priceRoad))
        throw logic_error("Player can't afford road");
    if (!board.canBuildRoad(players[playerIndex], plotIndex))
        throw logic_error("Player can't place road there");

    players[playerIndex].pay(priceRoad);
    board.buildRoad(players[playerIndex], plotIndex);
}

void Game::upgradeSettlement(unsigned int playerIndex, unsigned  int index) {
    if (!players[playerIndex].canAfford(priceCity))
        throw logic_error("Player can't afford upgrading");
    if (!board.canUpgradeVillage(players[playerIndex], index))
        throw logic_error("Player upgrade village there");

    players[playerIndex].pay(priceCity);
    board.upgradeVillage(players[playerIndex], index);
}

void Game::stealResources() {
    for (unsigned int i = 0; i < 3; i++) {
        if (players[i].sumResources() > 7)
            players[i].loseHalfResources();
    }
}
