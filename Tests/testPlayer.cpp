//
//
//
#include "../Game.hpp"
#include "../doctest.h"

TEST_CASE("Test resources") {
    Player player("Oriya");

    CHECK(player.getResourceCount(Resource::Brick) == 0);
    CHECK(player.getResourceCount(Resource::Wood) == 0);
    CHECK(player.getResourceCount(Resource::Wool) == 0);
    CHECK(player.getResourceCount(Resource::Oats) == 0);
    CHECK(player.getResourceCount(Resource::Iron) == 0);
    CHECK(player.sumResources() == 0);

    player.addResource(Resource::Brick, 5);
    player.addResource(Resource::Wood, 3);
    player.addResource(Resource::Wool, 2);

    CHECK(player.getResourceCount(Resource::Brick) == 5);
    CHECK(player.getResourceCount(Resource::Wood) == 3);
    CHECK(player.getResourceCount(Resource::Wool) == 2);
    CHECK(player.getResourceCount(Resource::Oats) == 0);
    CHECK(player.getResourceCount(Resource::Iron) == 0);
    CHECK(player.sumResources() == 10);

    map<Resource, unsigned int> price = {{Resource::Brick, 2}, {Resource::Wood, 1}};
    CHECK(player.canAfford(price));

    player.pay(price);
    CHECK(player.getResourceCount(Resource::Brick) == 3);
    CHECK(player.getResourceCount(Resource::Wood) == 2);

    map<Resource, unsigned int> price2 = {{Resource::Brick, 4}, {Resource::Wood, 1}};
    CHECK(!player.canAfford(price2));

    CHECK_THROWS_AS(player.pay(price2), std::logic_error);
    CHECK(player.getResourceCount(Resource::Brick) == 3);
    CHECK(player.getResourceCount(Resource::Wood) == 2);

    map<Resource, unsigned int> price3 = {{Resource::Brick, 1}, {Resource::Wood, 1}};
    player.pay(price3);
    CHECK(player.getResourceCount(Resource::Brick) == 2);
    CHECK(player.getResourceCount(Resource::Wood) == 1);

    map<Resource, unsigned int> price4 = {};
    CHECK(player.canAfford(price4));
    player.pay(price4);
    CHECK(player.getResourceCount(Resource::Brick) == 2);

    map<Resource, unsigned int> price5 = {{Resource::Brick, 1}, {Resource::Wood, 1}};
    player.receive(price5);
    CHECK(player.getResourceCount(Resource::Brick) == 3);
    CHECK(player.getResourceCount(Resource::Wood) == 2);
    CHECK(player.getResourceCount(Resource::Wool) == 2);
    CHECK(player.sumResources() == 7);

    player.loseHalfResources();
    CHECK(player.getResourceCount(Resource::Brick) == 1);
    CHECK(player.getResourceCount(Resource::Wood) == 1);
    CHECK(player.getResourceCount(Resource::Wool) == 1);
    CHECK(player.sumResources() == 3);

}

TEST_CASE("Test victory points") {
    Player player("Oriya");

    CHECK(player.getVictoryPoints() == 0);
    player.addVictoryPoint(2);
    CHECK(player.getVictoryPoints() == 2);
    player.addVictoryPoint(3);
    CHECK(player.getVictoryPoints() == 5);
    player.addVictoryPoint(1);
    CHECK(player.getVictoryPoints() == 6);
}

TEST_CASE("Test cards") {
    Player player("Oriya");

    CHECK(player.numCards("Knight") == 0);

    player.addDevelopmentCard("Knight");
    CHECK(player.numCards("Knight") == 1);

    player.addDevelopmentCard("Knight");
    CHECK(player.numCards("Knight") == 2);

    player.addDevelopmentCard("Knight");
    CHECK(player.numCards("Knight") == 3);

    player.removeCard("Knight");
    CHECK(player.numCards("Knight") == 2);

    player.removeCard("Knight");
    CHECK(player.numCards("Knight") == 1);

    player.removeCard("Knight");
    CHECK(player.numCards("Knight") == 0);

    CHECK_THROWS_AS(player.removeCard("Knight"), std::logic_error);

    player.addDevelopmentCard("Monopoly");
    CHECK(player.numCards("Monopoly") == 1);

}

TEST_CASE("Test play cards") {
    Game game("Oriya", "Adi", "Imri", "Tests/InputCards.txt");
    Player player = game.getPlayer(0);

    player.addDevelopmentCard("Knight");
    player.addDevelopmentCard("Knight");
    CHECK_THROWS(player.playDevelopmentCard("Knight", game));

    player.addDevelopmentCard("Knight");
    player.playDevelopmentCard("Knight", game);
    CHECK(player.numCards("Knight") == 0);
    CHECK(player.getVictoryPoints() == 2);

    CHECK_THROWS_AS(player.playDevelopmentCard("Knight", game), std::logic_error);

    player.addDevelopmentCard("Monopoly");
    player.addResource(Resource::Wood, 3);
    game.getPlayer(1).addResource(Resource::Wood, 2);
    game.getPlayer(2).addResource(Resource::Wood, 1);

    player.playDevelopmentCard("Monopoly", game);
    CHECK(player.getResourceCount(Resource::Wood) == 6);
    CHECK(game.getPlayer(1).getResourceCount(Resource::Wood) == 0);
    CHECK(game.getPlayer(2).getResourceCount(Resource::Wood) == 0);

//    CHECK_THROWS(player.playDevelopmentCard("Monopoly", game));
//
//    player.addDevelopmentCard("Points");
//    player.playDevelopmentCard("Points", game);
//    CHECK(player.getVictoryPoints() == 3);
//
//    game.placeSettlement(player, 0, true, true);
//    player.addDevelopmentCard("Roads");
//    player.playDevelopmentCard("Roads", game);
//    CHECK(game.isThereRoad(0));
//    CHECK(game.isThereRoad(6));
//
//    player.addDevelopmentCard("YearOfPlenty");
//    player.playDevelopmentCard("YearOfPlenty", game);
//    CHECK(player.getResourceCount(Resource::Brick) == 1);
//    CHECK(player.getResourceCount(Resource::Wool) == 1);

}

