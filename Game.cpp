#include "Game.hpp"
#include <iostream>
#include <random>
#include <memory>
#include <fstream>

using namespace std;
Game::Game(string name1, string name2, string name3, string dst) : rng(std::random_device()()), board() {
    // Initialize players
    players.emplace_back(name1);
    players.emplace_back(name2);
    players.emplace_back(name3);

    // Initialize development cards randomly
    initialize_dev_cards();

    // Set input source based on 'dst'
    if(dst == "") {
        input_file = make_unique<std::istream>(cin.rdbuf());
    }
    else {
        auto file = make_unique<ifstream>(dst);
        if(!file->is_open()) {
            throw std::runtime_error("Cannot open file: " + dst);
        }
        input_file = std::move(file);
    }
}

void Game::initialize_dev_cards() {
    unsigned int knights = 3;
    unsigned int roads = 3;
    unsigned int monopolies = 4;
    unsigned int years = 4;
    unsigned int points = 4;
    unsigned int sum = knights + roads + monopolies + years + points;

    developmentCards.resize(sum);

    // Populate developmentCards with random types
    for (unsigned int i = 0; i < sum; i++) {
        int r = rand()%5;
        if (r == 0 && knights > 0) {
            developmentCards[i] = make_unique<KnightCard>();
            knights--;
        }
        else if (r == 1 && roads > 0) {
            developmentCards[i] = make_unique<RoadsCard>();
            roads--;
        }
        else if (r == 2 && monopolies > 0) {
            developmentCards[i] = make_unique<MonopolyCard>();
            monopolies--;
        }
        else if (r == 3 && years > 0) {
            developmentCards[i] = make_unique<YearOfPlentyCard>();
            years--;
        }
        else if (r == 4 && points > 0) {
            developmentCards[i] = make_unique<PointsCard>();
            points--;
        }
        else {
            i--; // Retry if none of the conditions were met
        }
    }
}


Player& Game::getPlayer(unsigned int index) {
    return players.at(index);
}

void Game::printBoard() const {
    std::cout << "Game Board:" << std::endl;
    std::cout << board.toString() << std::endl;
}

void Game::printPlayers() const {
    std::cout << "Players:" << std::endl;
    for (const auto& player : players) {
        std::cout << player.getName() << std::endl;
    }
}

unsigned int Game::rollDice() {
    std::uniform_int_distribution<unsigned int> dist(1, 6); // Distribution for a six-sided die
    return dist(rng) + dist(rng); // Roll two dice and return the sum
}

void Game::rollDiceAndProcessResult(unsigned int setResult) {
    unsigned int rollResult = rollDice();
    if (setResult != 0) {
        rollResult = setResult;
    }
    std::cout << "Dice roll: " << rollResult << std::endl;

    if (rollResult != 7) {
        board.produce(rollResult);
    } else {
        stealResources();
    }
}

void Game::placeSettlement(Player& player,unsigned int plotIndex, bool free, bool first) {
    if (!free && !player.canAfford(priceVillage))
        throw logic_error("Player can't afford village");
    if (first) {
        if (!board.canBuildFirstVillage(player, plotIndex))
            throw logic_error("Player can't place first village");
    } else if (!board.canBuildVillage(player, plotIndex))
        throw logic_error("Player can't place village there");

    if (!free)
        player.pay(priceVillage);
    player.addVictoryPoint(1);
    board.buildVillage(player, plotIndex, first);
}

void Game::placeRoad(Player& player, unsigned int plotIndex, bool free) {
    if (!free && !player.canAfford(priceRoad))
        throw logic_error("Player can't afford road");
    if (!board.canBuildRoad(player, plotIndex))
        throw logic_error("Player can't place road there");

    if (!free)
        player.pay(priceRoad);
    board.buildRoad(player, plotIndex);
}

void Game::upgradeSettlement(Player& player, unsigned  int index) {
    if (!player.canAfford(priceCity))
        throw logic_error("Player can't afford upgrading");
    if (!board.canUpgradeVillage(player, index))
        throw logic_error("Player upgrade village there");

    player.pay(priceCity);
    player.addVictoryPoint(1);
    board.upgradeVillage(player, index);
}

void Game::stealResources() {
    for (unsigned int i = 0; i < 3; i++) {
        if (players[i].sumResources() > 7)
            players[i].loseHalfResources();
    }
}

void Game::firstRound() {
    unsigned int inputIndex = 999;
    for (unsigned int i = 0; i < 3; i++) {
        cout << "Hello " << players[i].getName() << ", please enter a starting position for a village" << endl;
        *input_file >> inputIndex;
        placeSettlement(players[i], inputIndex, true, true);

        cout << "Hello again " << players[i].getName() << ", please enter a starting position for a road" << endl;
        *input_file >> inputIndex;
        placeRoad(players[i], inputIndex, true);
    }
    for (unsigned int i = 2; 1; i--) {
        cout << "Hello " << players[i].getName() << ", please enter a starting position for a village" << endl;
        *input_file >> inputIndex;
        placeSettlement(players[i], inputIndex, true, true);

        cout << "Hello again " << players[i].getName() << ", please enter a starting position for a road" << endl;
        *input_file >> inputIndex;
        placeRoad(players[i], inputIndex, true);

        if (i == 0) break;
    }

    for (unsigned int i = 2; i < 12; i++) {
        if (i == 7) continue;
        rollDiceAndProcessResult(i);
    }
}

Game::Turn Game::chooseTurn() const {
    std::cout << "Choose a turn:" << std::endl;
    std::cout << "1. Build Road" << std::endl;
    std::cout << "2. Build Village" << std::endl;
    std::cout << "3. Upgrade Village" << std::endl;
    std::cout << "4. Play Development Card" << std::endl;
    std::cout << "5. Buy Development Card" << std::endl;
    std::cout << "6. Trade Card" << std::endl;
    std::cout << "7. Trade Resource" << std::endl;
    std::cout << "8. End Turn" << std::endl;

    unsigned int input = 0;
    *input_file >> input;

    switch (input) {
        case 1:
            return Turn::BuildRoad;
        case 2:
            return Turn::BuildVillage;
        case 3:
            return Turn::UpgradeVillage;
        case 4:
            return Turn::PlayDevCard;
        case 5:
            return Turn::BuyDevCard;
        case 6:
            return Turn::TradeCard;
        case 7:
            return Turn::TradeResource;
        case 8:
            return Turn::EndTurn;
        default:
            throw logic_error("Invalid input");
    }
}

void Game::playTurn(Player& player) {
    rollDiceAndProcessResult();

    unsigned int input = 999;
    string inputString = "";
    while (true) {
        player.printResources();
        player.printCards();
        Turn turn = chooseTurn();
        switch (turn) {
            case Turn::BuildRoad:

                try {
                    cout << "Hello " << player.getName() << ", please enter a position for a road" << endl;
                    *input_file >> input;
                    placeRoad(player, input);
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }

                break;
            case Turn::BuildVillage:
                try {
                    cout << "Hello " << player.getName() << ", please enter a position for a village" << endl;
                    *input_file >> input;
                    placeSettlement(player, input);
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }

                break;
            case Turn::UpgradeVillage:
                try {
                    cout << "Hello " << player.getName() << ", please enter a position for a village upgrade" << endl;
                    *input_file >> input;
                    upgradeSettlement(player, input);
                } catch (const logic_error& e) {
                    cout << e.what() << endl;
                }

                break;

            case Turn::PlayDevCard:
                cout << "Hello " << player.getName() << ", please enter a development card" << endl;
                *input_file >> inputString;
                player.playDevelopmentCard(inputString, *this);
                break;
            case Turn::BuyDevCard:
                buyCard(player);
                break;

            case Turn::TradeCard:
                tradeCard(player);
                break;
            case Turn::TradeResource:
                tradeResources(player);
                break;

            case Turn::EndTurn:
                return;
        }
    }

}

void Game::buyCard(Player &player) {
    if (!player.canAfford(priceDev))
        throw logic_error("Player can't afford card");
    if (currentCard >= developmentCards.size())
        throw logic_error("No more cards left");

    player.addDevelopmentCard(developmentCards[currentCard]->toString());
    currentCard++;
}

map<Resource, unsigned int> Game::enterPrice()
{
    std::cout<<"Wood, Brick, Wool, Oats, Iron"<<std::endl;
    map<Resource,unsigned int> price;
    *input_file >> price[Resource::Wood]>>price[Resource::Brick]>>price[Resource::Wool]>>price[Resource::Oats]>>price[Resource::Iron];
    return price;
}
void Game::tradeResources(Player & p) {
    std::cout<< "Enter what do you want to get. "<< std::endl;
    map<Resource,unsigned int> buyPrice = enterPrice();
    std::cout<< "Enter what do you want to give. "<< std::endl;
    map<Resource,unsigned int> sellPrice = enterPrice();
    if (!p.canAfford(sellPrice))
        throw logic_error("Player can't afford trade");

    for (unsigned int i = 0; i < 3; i++) {
        if (players[i].getName() == p.getName()) continue;

        if (players[i].canAfford(buyPrice)) {
            cout << "Hello" << players[i].getName() << ", do you want to trade? (y/n)" << endl;
            char input = 'n';
            *input_file >> input;
            if (input != 'y') continue;

            p.pay(sellPrice);
            players[i].receive(sellPrice);

            p.receive(buyPrice);
            players[i].pay(buyPrice);
            return;
        }
    }
}

void Game::tradeCard(Player &p) {

    std::cout<< "Enter what do you want to get. "<< std::endl;
    string buyCard = "";
    *input_file >> buyCard;

    std::cout<< "Enter what do you want to give. "<< std::endl;
    string sellCard = "";
    *input_file >> sellCard;
    if (p.numCards(sellCard) == 0) {
        throw logic_error("Player does not have card");
    }

    for (unsigned int i = 0; i < 3; i++) {
        if (players[i].getName() == p.getName()) continue;

        if (players[i].numCards(buyCard) > 0) {
            cout << "Hello" << players[i].getName() << ", do you want to trade? (y/n)" << endl;
            char input = 'n';
            *input_file >> input;
            if (input != 'y') continue;

            p.removeCard(sellCard);
            players[i].addDevelopmentCard(sellCard);

            p.addDevelopmentCard(buyCard);
            players[i].removeCard(buyCard);
            return;
        }
    }
}

void Game::start() {
    firstRound();
    while (true) {
        for (auto& player : players) {
            printBoard();
            cout << "=========== It's " << player.getName() << "'s turn ===========" << endl;
            playTurn(player);
            if (player.getVictoryPoints() >= 10) {
                std::cout << player.getName() << " wins!" << std::endl;
                return;
            }
        }
    }
}

std::istream *Game::get_input() {
    return input_file.get();
}


