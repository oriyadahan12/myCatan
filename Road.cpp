//
//oriyati0701@gmail.com

//

#include "Road.hpp"

/// @brief Builds the road for the specified player.
void Road::build(Player& player) {
    if (!built) {
        owner = &player;
        built = true;
    } else {
        throw std::logic_error("Road already built");
    }
}
