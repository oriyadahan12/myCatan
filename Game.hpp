//oriyati0701@gmail.com

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
    enum class Turn {
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
    // Prices for various game actions
    map<Resource, unsigned int> priceRoad = {{Resource::Wood, 1}, {Resource::Brick, 1}};
    map<Resource, unsigned int> priceVillage = {{Resource::Wood, 1}, {Resource::Brick, 1}, {Resource::Wool, 1}, {Resource::Oats, 1}};
    map<Resource, unsigned int> priceCity = {{Resource::Oats, 2}, {Resource::Iron, 3}};
    map<Resource, unsigned int> priceDev = {{Resource::Iron, 1}, {Resource::Wool, 1}, {Resource::Oats, 1}};

    // Constructors and main functions
    Game(string name1, string name2, string name3, string dst = "");
    void start();
    Player& getPlayer(unsigned int index);

    // Print functions
    void printBoard() const;
    void printPlayers() const;

    // Game mechanics functions
    Turn chooseTurn() const;
    void rollDiceAndProcessResult(unsigned int setResult = 0);
    void initialize_dev_cards();
    void stealResources();
    void buyCard(Player&);
    void tradeResources(Player&);
    void tradeCard(Player&);

    // Board manipulation functions
    void placeSettlement(Player& player, unsigned int index, bool free = false, bool first = false);
    void placeRoad(Player& player, unsigned int index, bool free = false);
    void upgradeSettlement(Player& player, unsigned int index);

    // Board state queries
    bool isThereRoad(unsigned int index) const { return board.isThereRoad(index); }
    bool isThereVillage(unsigned int index) const { return board.isThereVillage(index); }

    // Initial setup functions
    void firstRound();
    void playTurn(Player&);

    // Helper functions
    map<Resource, unsigned int> enterPrice();
    std::istream* get_input();

private:
    std::vector<Player> players;
    Board board;
    std::mt19937 rng; // Random number generator

    unsigned int rollDice(); // Rolls the dice and returns the result

    // Development cards management
    vector<unique_ptr<DevelopmentCard>> developmentCards;
    unsigned int currentCard = 0;

    unique_ptr<std::istream> input_file; // Optional input file for game initialization
};

#endif // GAME_H
