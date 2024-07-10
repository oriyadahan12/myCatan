//
// Created by magshimim on 7/4/24.
//

#ifndef NEWCATAN_ROAD_HPP
#define NEWCATAN_ROAD_HPP

#include "Player.hpp"

class Road {
private:
    Player* owner; ///< Pointer to the player who owns the road.
    bool built = false; ///< Boolean indicating whether the road is built or not.

public:
    /// @brief Constructs a Road object.
    Road() {}

    /// @brief Checks if the road is built.
    bool isBuilt() const { return built; }

    /// @brief Builds the road for the specified player.
    void build(Player& player);

    /// @brief Gets the owner of the road.
    Player* getOwner() const { return owner; }
};

#endif //NEWCATAN_ROAD_HPP
