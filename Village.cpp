//
// Created by magshimim on 7/4/24.
//

#include "Village.hpp"
void Village::build(Player& player){
    if (type == Type::None){
        type = Type::Settlement;
        owner = &player;
    }
    else{
        throw std::invalid_argument("Village already built");
    }
}
void Village::upgrade(){
    if (type == Type::Settlement){
        type = Type::City;
    }
    else{
        throw std::invalid_argument("Village already upgraded");
    }
}
void Village::receive(Resource r){
        owner->addResource(r,static_cast<unsigned int>(type));
}
