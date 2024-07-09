//
// Created by magshimim on 7/4/24.
//

#ifndef NEWCATAN_ROAD_HPP
#define NEWCATAN_ROAD_HPP
#include "Player.hpp"

class Road {
private:
    Player* owner;
    bool built=false;
public:
    Road(){}
    bool isBuilt() const {return built;}
    void build(Player& player);
    Player* getOwner() const {return owner;}
};


#endif //NEWCATAN_ROAD_HPP
