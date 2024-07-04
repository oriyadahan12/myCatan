#include "Player.hpp"
#include "Board.hpp"
#include "development_card.hpp"
#include <vector>
#include <iostream>

// Function to initialize the game
void initializeGame() {
    const int NUM_PLAYERS = 4; // Adjust as needed
    std::vector<Player> players;

    // Create players
    for (int i = 0; i < NUM_PLAYERS; ++i) {
        std::string playerName = "Player " + std::to_string(i + 1);
        Player player(playerName);
        players.push_back(player);
    }

    // Initialize game board with appropriate dimensions (example: 3x3)
    Board gameBoard(3, 3);

    // Distribute initial resources and settlements to players
    gameBoard.placeInitialSettlements(players);

    // Example: Distribute initial resources to each player
    for (int i = 0; i < players.size(); ++i) {
        players[i].addResource(Resource::Wood, 2);
        players[i].addResource(Resource::Brick, 2);
        players[i].addResource(Resource::Wool, 2);
        players[i].addResource(Resource::Oats, 2);
        players[i].addResource(Resource::Iron, 2);

        // Example: Give each player some initial development cards if needed
        DevelopmentCard initialCard(DevelopmentCard::Type::Knight);
        players[i].addDevelopmentCard(initialCard);
    }

    // Start the game loop or allow players to take their turns from here
    // Example: Simple game loop
    bool gameRunning = true;
    while (gameRunning) {
        for (Player& player : players) {
            // Example: Player takes a turn
            // You can implement a function like player.takeTurn() to handle player's actions
            // For now, just print the player's name and their resources
            std::cout << player.getName() << "'s turn." << std::endl;
            std::cout << "Resources: " << std::endl;
            std::cout << "  Wood: " << player.getResourceCount(Resource::Wood) << std::endl;
            std::cout << "  Brick: " << player.getResourceCount(Resource::Brick) << std::endl;
            std::cout << "  Wool: " << player.getResourceCount(Resource::Wool) << std::endl;
            std::cout << "  Oats: " << player.getResourceCount(Resource::Oats) << std::endl;
            std::cout << "  Iron: " << player.getResourceCount(Resource::Iron) << std::endl;

            // Placeholder for ending the game loop
            // Implement actual game end condition check
            gameRunning = false; // Example: End game after one loop
        }
    }
}
