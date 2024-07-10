# Settlers of Catan Simplified
//oriyati0701@gmail.com

A simplified version of the Settlers of Catan game for three players, implemented in C++. This project simulates resource production, village building, and road construction on a game board.

## Table of Contents
- [Overview](#overview)
- [Game Mechanics](#game-mechanics)
- [Code Structure](#code-structure)
- [Class Details](#class-details)
    - [Game](#game)
    - [Board](#board)
    - [Plot](#plot)
    - [Player](#player)
    - [Road](#road)
    - [Village](#village)
- [Usage](#usage)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [License](#license)

## Overview

This project is a simplified version of the Settlers of Catan game, designed for three players. The game is implemented in C++ and involves creating a game board with plots, roads, and villages. Players can produce resources, build roads, and construct or upgrade villages.

## Game Mechanics

- **Resource Production**: Players roll a dice, and the corresponding plots produce resources for the adjacent villages.
- **Village and Road Construction**: Players can build roads and villages on the board if they have the required resources and meet the conditions.
- **Village Upgradation**: Villages can be upgraded to provide additional benefits.

## Code Structure

The codebase is organized into several classes, each responsible for different aspects of the game:

- `Game`: Manages the overall game logic and player interactions.
- `Board`: Manages the game board, including plots, roads, and villages.
- `Plot`: Represents a plot on the game board that can produce resources.
- `Player`: Represents a player in the game, managing resources and actions.
- `Road`: Represents a road that can be built on the board.
- `Village`: Represents a village that can be built and upgraded.

## Class Details

### Game

The `Game` class manages the overall game logic and player interactions.

- **Member Variables**:
    - `std::vector<Player> players`: A vector of all players in the game.
    - `Board board`: The game board.
    - `std::mt19937 rng`: Random number generator.
    - `std::map<Resource, unsigned int> priceRoad`: Prices for building roads.
    - `std::map<Resource, unsigned int> priceVillage`: Prices for building villages.
    - `std::map<Resource, unsigned int> priceCity`: Prices for upgrading villages to cities.
    - `std::map<Resource, unsigned int> priceDev`: Prices for buying development cards.
    - `std::vector<unique_ptr<DevelopmentCard>> developmentCards`: A vector of development cards.
    - `unsigned int currentCard`: Index of the current development card.
    - `unique_ptr<std::istream> input_file`: Optional input file for game initialization.

- **Member Functions**:
    - `Game(std::string name1, std::string name2, std::string name3, std::string dst = "")`: Constructor that initializes the game with three players.
    - `void start()`: Starts the game.
    - `Player& getPlayer(unsigned int index)`: Returns the player at the given index.
    - `void printBoard() const`: Prints the current state of the game board.
    - `void printPlayers() const`: Prints the current state of the players.
    - `Turn chooseTurn() const`: Chooses the next turn.
    - `void rollDiceAndProcessResult(unsigned int setResult = 0)`: Rolls the dice and processes the result.
    - `void initialize_dev_cards()`: Initializes the development cards.
    - `void stealResources()`: Steals resources from other players.
    - `void buyCard(Player&)`: Allows a player to buy a development card.
    - `void tradeResources(Player&)`: Allows a player to trade resources.
    - `void tradeCard(Player&)`: Allows a player to trade development cards.
    - `void placeSettlement(Player& player, unsigned int index, bool free = false, bool first = false)`: Places a settlement on the board.
    - `void placeRoad(Player& player, unsigned int index, bool free = false)`: Places a road on the board.
    - `void upgradeSettlement(Player& player, unsigned int index)`: Upgrades a settlement.
    - `bool isThereRoad(unsigned int index) const`: Checks if there is a road at the given index.
    - `bool isThereVillage(unsigned int index) const`: Checks if there is a village at the given index.
    - `void firstRound()`: Conducts the first round of the game.
    - `void playTurn(Player&)`: Conducts a player's turn.
    - `std::map<Resource, unsigned int> enterPrice()`: Prompts the user to enter resource prices.
    - `std::istream* get_input()`: Returns the input stream.
    - `unsigned int rollDice()`: Rolls the dice and returns the result.

### Board

The `Board` class is the core of the game, managing the state and interactions of the game board.

- **Member Variables**:
    - `std::vector<Plot> plots`: A vector of all plots on the board.
    - `std::vector<Road> roads`: A vector of all roads on the board.
    - `std::vector<Village> villages`: A vector of all villages on the board.

- **Member Functions**:
    - `Board()`: Constructor that initializes the game board.
    - `void initializePlots()`: Initializes the plots on the board with predefined resources.
    - `void produce(unsigned int diceNum)`: Simulates resource production based on a dice roll.
    - `void buildRoad(Player& player, unsigned int roadIndex)`: Allows a player to build a road.
    - `void buildVillage(Player& player, unsigned int villageIndex, bool first = false)`: Allows a player to build a village.
    - `void upgradeVillage(Player& player, unsigned int villageIndex)`: Allows a player to upgrade a village.
    - `bool canBuildRoad(Player& player, unsigned int roadIndex) const`: Checks if a player can build a road.
    - `bool canBuildFirstVillage(Player& player, unsigned int villageIndex) const`: Checks if a player can build their first village.
    - `bool canBuildVillage(Player& player, unsigned int villageIndex) const`: Checks if a player can build a village.
    - `bool canUpgradeVillage(Player& player, unsigned int villageIndex) const`: Checks if a player can upgrade a village.
    - `bool isThereRoad(unsigned int index) const`: Checks if there is a road at the given index.
    - `bool isThereVillage(unsigned int index) const`: Checks if there is a village at the given index.
    - `std::string toString() const`: Returns a string representation of the board.

### Plot

The `Plot` class represents a plot on the game board.

- **Member Variables**:
    - `Resource type`: The type of resource the plot produces.

- **Member Functions**:
    - `Plot(Resource type)`: Constructor that initializes the plot with a resource type.
    - `Resource getType() const`: Returns the resource type of the plot.
    - `std::string toString() const`: Returns a string representation of the plot.

### Player

The `Player` class represents a player in the game.

- **Member Variables**:
    - `unsigned int id`: The player's ID.
    - `std::map<Resource, unsigned int> resources`: A map of the player's resources.

- **Member Functions**:
    - `Player(unsigned int id)`: Constructor that initializes the player with an ID.
    - `bool checkResources(unsigned int brick, unsigned int wood, unsigned int iron, unsigned int oats, unsigned int wool)`: Checks if the player has the required resources.
    - `void receive(Resource resource)`: Adds a resource to the player's inventory.

### Road

The `Road` class represents a road that can be built on the board.

- **Member Variables**:
    - `Player* owner`: The player who owns the road.
    - `bool built`: Indicates if the road is built.

- **Member Functions**:
    - `Road()`: Constructor that initializes the road.
    - `void build(Player& player)`: Builds the road for the player.
    - `bool isBuilt() const`: Checks if the road is built.
    - `Player* getOwner() const`: Returns the owner of the road.

### Village

The `Village` class represents a village that can be built and upgraded.

- **Member Variables**:
    - `Player* owner`: The player who owns the village.
    - `bool built`: Indicates if the village is built.
    - `unsigned int level`: The level of the village.

- **Member Functions**:
    - `Village()`: Constructor that initializes the village.
    - `void build(Player& player)`: Builds the village for the player.
    - `void upgrade()`: Upgrades the village.
    - `bool isbuilt() const`: Checks if the village is built.
    - `Player* getOwner() const`: Returns the owner of the village.

## Usage

The game is controlled through commands executed in the main game loop. Here are some examples of how to use the functions:

1. **Initialize the Game**:
    ```cpp
    Game game("Oriya", "Adi", "Imri");
    ```

2. **Start the Game**:
    ```cpp
    game.start();
    ```

3. **Print the Board and Players**:
    ```cpp
    game.printBoard();
    game.printPlayers();
    ```

4. **Conduct Player Turns**:
    ```cpp
    game.playTurn(game.getPlayer(0));
    ```

## Future Enhancements

- Add network support for multiplayer games.
- Implement additional features like trading and more complex game strategies.
- Improve the user interface and add graphical representations of the board.


    Thank you for reading! If you have any suggestions or feedback, feel free to reach out.
    love you all.



