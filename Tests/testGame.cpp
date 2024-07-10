#include "../doctest.h"
#include "../Game.hpp"

TEST_CASE("Test rolling dice"){
    Game game("Oriya","Adi","Imri");

    game.placeSettlement(game.getPlayer(0), 0, true, true);
    CHECK_THROWS(game.placeSettlement(game.getPlayer(1), 4, true, true));
    game.placeSettlement(game.getPlayer(1), 8, true, true);
    CHECK(game.getPlayer(0).sumResources() == 0);
    CHECK(game.getPlayer(1).sumResources() == 0);
    game.rollDiceAndProcessResult(10);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Brick) == 1);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Brick) == 1);

    game.rollDiceAndProcessResult(2);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Wood) == 0);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Wood) == 1);

    game.rollDiceAndProcessResult(7);
    CHECK(game.getPlayer(0).sumResources() == 1);
    CHECK(game.getPlayer(1).sumResources() == 2);

    game.getPlayer(0).addResource(Resource::Oats, 10);
    game.getPlayer(1).addResource(Resource::Iron, 10);
    game.rollDiceAndProcessResult(7);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Oats) == 5);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Brick) == 0);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Wood) == 0);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Iron) == 5);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Brick) == 0);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Wood) == 0);

}

TEST_CASE("Test trading") {
    Game game("Oriya","Adi","Imri", "Tests/InputTrading.txt");

    game.getPlayer(0).addResource(Resource::Oats, 10);
    game.getPlayer(0).addResource(Resource::Iron, 10);
    game.getPlayer(1).addResource(Resource::Wood, 10);
    game.getPlayer(1).addResource(Resource::Wool, 10);

    game.tradeResources(game.getPlayer(0));
    CHECK(game.getPlayer(0).getResourceCount(Resource::Oats) == 5);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Iron) == 3);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Wood) == 6);
    CHECK(game.getPlayer(0).getResourceCount(Resource::Wool) == 6);

    CHECK(game.getPlayer(1).getResourceCount(Resource::Wood) == 4);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Wool) == 4);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Oats) == 5);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Iron) == 7);


}
