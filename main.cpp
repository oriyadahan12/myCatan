#include "Game.hpp"
#include <iostream>

int main() {
    Game game("Oriya", "Adi", "Imri");
    game.printBoard();
    game.printPlayers();

    return 0;
}
