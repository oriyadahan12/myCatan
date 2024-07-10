//
// Created by magshimim on 7/4/24.
//

#include "Village.hpp"

/// @brief Builds a village for the specified player.
/// @param player Reference to the player who will own the village.
/// @throws std::invalid_argument if the village is already built.
void Village::build(Player& player) {
    if (type == Type::None) {
        type = Type::Settlement;
        owner = &player;
    } else {
        throw std::invalid_argument("Village already built");
    }
}

/// @brief Upgrades the village from a settlement to a city.
/// @throws std::invalid_argument if the village is already a city or not yet a settlement.
void Village::upgrade() {
    if (type == Type::Settlement) {
        type = Type::City;
    } else {
        throw std::invalid_argument("Village already upgraded");
    }
}

/// @brief Receives a resource and adds it to the owner.
/// @param r The resource to be received.
void Village::receive(Resource r) {
    if (type == Type::None) return;
    owner->addResource(r, static_cast<unsigned int>(type));
}
