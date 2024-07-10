//oriyati0701@gmail.com

#include "development_card.hpp"
#include "Game.hpp"
#include "Player.hpp"

void KnightCard::play(Player &player, Game &game) {
    if (player.numCards("Knight") >= 3) {
        player.addVictoryPoint(2);
        player.removeCard("Knight");
        player.removeCard("Knight");
    } else {
        throw std::logic_error("Player does not have enough knights");
    }
}

void MonopolyCard::play(Player &player, Game &game) {
    std::cout << "enter resource please: " << std::endl;
    unsigned int input = 0;
    *game.get_input() >> input;
    Resource resource = intToResource(input);
    cout << "resource: " << resourceToString(resource) << endl;

    for (unsigned int i = 0; i < 3; i++) {
        if (player.getName() == game.getPlayer(i).getName()) continue;

        unsigned int transfer = game.getPlayer(i).getResourceCount(resource);
        game.getPlayer(i).loseResource(resource, transfer);
        player.addResource(resource, transfer);
    }
}

void PointsCard::play(Player &player, Game &game) {
    player.addVictoryPoint(1);
}

void RoadsCard::play(Player &player, Game &game) {
    while (true) {
        try {
            std::cout << "enter index for road please: " << std::endl;
            unsigned int input = 0;
            *game.get_input() >> input;
            game.placeRoad(player, input);
            break;
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }
    while (true) {
        try {
            std::cout << "enter index for road please: " << std::endl;
            unsigned int input = 0;
            *game.get_input() >> input;
            game.placeRoad(player, input);
            break;
        } catch (const std::exception& e) {
            cout << e.what() << endl;
        }
    }

}

void YearOfPlentyCard::play(Player &player, Game &game) {
    std::cout << "enter resource please: " << std::endl;
    unsigned int input = 0;
    *game.get_input() >> input;
    Resource resource = intToResource(input);
    player.addResource(resource, 1);

    std::cout << "enter resource please: " << std::endl;
    *game.get_input() >> input;
    resource = intToResource(input);
    player.addResource(resource, 1);
}
