#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include <string>
#include "Player.hpp"
#include "Plot.hpp"
#include "Board.hpp"

using namespace std;
class Game {
public:
    map<Resource,unsigned int> priceRoad = {{Resource::Wood, 1}, {Resource::Brick, 1}};
    map<Resource, unsigned int> priceVillage = {{Resource::Wood, 1}, {Resource::Brick, 1},{Resource::Wool, 1},{Resource::Oats, 1}};
    map<Resource, unsigned int> priceCity = {{Resource::Oats, 2}, {Resource::Iron, 3}};
    map<Resource,unsigned int> priceDev ={{Resource::Iron, 1}, {Resource::Wool, 1}, {Resource::Oats,1}};

    Game(string name1, string name2, string name3);
    Player& getPlayer(unsigned int index);
    void printBoard() const;
    void printPlayers();
    void rollDiceAndProcessResult();

    void placeSettlement(unsigned int playerIndex, unsigned int index);
    void placeRoad(unsigned int playerIndex, unsigned int index);
    void upgradeSettlement(unsigned int playerIndex, unsigned int index);

    void stealResources();

private:
    std::vector<Player> players;
    Board board;
    std::mt19937 rng;

    unsigned int rollDice();

};

#endif // GAME_H
