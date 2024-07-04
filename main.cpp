#include "Game.hpp"
#include <iostream>

int main() {
    Game game;
    game.addPlayer("Oriya");
    game.addPlayer("Adi");
    game.addPlayer("Imri");

    game.printBoard();
    game.printPlayers();

    // Loop through each player and let them choose their initial settlements
    for (int i = 0; i < game.numPlayers; ++i) {
        std::cout << game.getPlayer(i).getName() << ", choose your initial settlements:" << std::endl;

        // Print available plots for the player to choose from
        game.printAvailablePlots();

        // Let the player choose two plots
        for (int j = 0; j < 2; ++j) {
            int choice;
            std::cout << "Enter plot number for settlement " << j + 1 << ": ";
            std::cin >> choice;

            // Validate the choice
            if (choice >= 1 && choice <= game.getBoardSize()) {
                game.placeSettlement(i, choice - 1); // Adjusting for zero-indexing
            } else {
                std::cout << "Invalid choice. Choose again." << std::endl;
                --j; // Retry the current selection
            }
        }
    }

    // Roll dice and distribute resources
    game.rollDiceAndDistributeResources();

    // Print each player's resources after rolling dice
    for (int i = 0; i < game.numPlayers; ++i) {
        Player& player = game.getPlayer(i);
        std::cout << player.getName() << "'s Resources after rolling dice:" << std::endl;
        std::cout << "Wood: " << player.getResourceCount(Resource::Wood) << std::endl;
        std::cout << "Brick: " << player.getResourceCount(Resource::Brick) << std::endl;
        std::cout << "Wool: " << player.getResourceCount(Resource::Wool) << std::endl;
        std::cout << "Oats: " << player.getResourceCount(Resource::Oats) << std::endl;
        std::cout << "Iron: " << player.getResourceCount(Resource::Iron) << std::endl;
    }

    // Place a city for Alice (for demonstration purposes)
    game.placeCity(0, 0);

    // Roll dice and distribute resources again
    game.rollDiceAndDistributeResources();

    // Print each player's resources after placing a city and rolling dice
    for (int i = 0; i < game.numPlayers; ++i) {
        Player& player = game.getPlayer(i);
        std::cout << player.getName() << "'s Resources after placing a city and rolling dice:" << std::endl;
        std::cout << "Wood: " << player.getResourceCount(Resource::Wood) << std::endl;
        std::cout << "Brick: " << player.getResourceCount(Resource::Brick) << std::endl;
        std::cout << "Wool: " << player.getResourceCount(Resource::Wool) << std::endl;
        std::cout << "Oats: " << player.getResourceCount(Resource::Oats) << std::endl;
        std::cout << "Iron: " << player.getResourceCount(Resource::Iron) << std::endl;
    }

    return 0;
}
