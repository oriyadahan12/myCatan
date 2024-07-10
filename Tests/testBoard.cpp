//
//
//
#include "../Board.hpp"
#include "../doctest.h"

TEST_CASE("Test placing"){
    Board board;
    Player p1("Oriya");
    Player p2("Yael");
    CHECK(board.canBuildFirstVillage(p1,1));
    CHECK(board.canBuildFirstVillage(p2,1));

    board.buildVillage(p1,1,true);
    CHECK(board.isThereVillage(1));

    CHECK_FALSE(board.canBuildFirstVillage(p2,1));
    CHECK_FALSE(board.canBuildRoad(p1,1));

    CHECK(board.canBuildRoad(p1,2));
    board.buildRoad(p1,2);
    CHECK(board.isThereRoad(2));

    CHECK(board.canBuildFirstVillage(p2,2));
    board.buildVillage(p2,2,true);

    CHECK_FALSE(board.canBuildRoad(p2,3));
    CHECK_THROWS(board.buildRoad(p2,3));

    board.produce(11);
    CHECK(p1.sumResources() == 0);
    CHECK(p2.sumResources() == 0);
    board.produce(2);
    CHECK(p1.getResourceCount(Resource::Wood) == 1);
    CHECK(p2.getResourceCount(Resource::Wood) == 0);

}