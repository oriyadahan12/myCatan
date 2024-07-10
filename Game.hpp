#ifndef GAME_H
#define GAME_H

#include <vector>
#include <random>
#include <string>
#include <memory>
#include "Player.hpp"
#include "Plot.hpp"
#include "Board.hpp"

using namespace std;
class Game {
    enum class Turn{
        BuildRoad,
        BuildVillage,
        UpgradeVillage,
        PlayDevCard,
        BuyDevCard,
        TradeCard,
        TradeResource,
        EndTurn
    };

public:
    map<Resource,unsigned int> priceRoad = {{Resource::Wood, 1}, {Resource::Brick, 1}};
    map<Resource, unsigned int> priceVillage = {{Resource::Wood, 1}, {Resource::Brick, 1},{Resource::Wool, 1},{Resource::Oats, 1}};
    map<Resource, unsigned int> priceCity = {{Resource::Oats, 2}, {Resource::Iron, 3}};
    map<Resource,unsigned int> priceDev ={{Resource::Iron, 1}, {Resource::Wool, 1}, {Resource::Oats,1}};

    Game(string name1, string name2, string name3);
    void start();
    Player& getPlayer(unsigned int index);

    void printBoard() const;
    void printPlayers() const;

    Turn chooseTurn() const;

    void rollDiceAndProcessResult(unsigned int setResult = 0);
    void initialize_dev_cards();
    void stealResources();
    void buyCard(Player&);
    void tradeResources(Player&);
    void tradeCard(Player&);

    void placeSettlement(Player& player, unsigned int index, bool free = false, bool first = false);
    void placeRoad(Player& player, unsigned int index, bool free = false);
    void upgradeSettlement(Player& player, unsigned int index);

    void firstRound();
    void playTurn(Player&);

private:
    std::vector<Player> players;
    Board board;
    std::mt19937 rng;

    unsigned int rollDice();
    vector<unique_ptr<DevelopmentCard>> developmentCards;
    unsigned int currentCard = 0;

};

#endif // GAME_H
