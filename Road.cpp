//
// Created by magshimim on 7/4/24.
//

#include "Road.hpp"

void Road::build(Player& player) {
    if(!built){
        owner=&player;
        built=true;
    }
    else{
        throw std::logic_error("Road already built");
    }
}
