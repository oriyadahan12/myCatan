//
//oriyati0701@gmail.com
//

#ifndef NEWCATAN_VILLAGE_HPP
#define NEWCATAN_VILLAGE_HPP

#include "Player.hpp"

/// @class Village
/// @brief Represents a village in the New Catan game.
class Village {
private:
    Player* owner; ///< Pointer to the player who owns the village.

    /// @brief Enumeration of the types of villages.
    enum class Type : unsigned int {
        None = 0,       ///< No village.
        Settlement = 1, ///< Settlement type village.
        City = 2        ///< City type village.
    };

    Type type; ///< The type of the village.

public:
    /// @brief Constructs a Village object with no type.
    Village(): type(Type::None) {}

    /// @brief Builds a village for the specified player.
    /// @param player Reference to the player who will own the village.
    void build(Player& player);

    /// @brief Upgrades the village from a settlement to a city.
    void upgrade();

    /// @brief Receives a resource.
    /// @param r The resource to be received.
    void receive(Resource r);

    /// @brief Checks if the village is built.
    /// @return An unsigned int representing the type of the village (0: None, 1: Settlement, 2: City).
    unsigned int isbuilt() const { return static_cast<unsigned int>(type); }

    /// @brief Gets the owner of the village.
    /// @return A pointer to the player who owns the village.
    Player* getOwner() const { return owner; }
};

#endif //NEWCATAN_VILLAGE_HPP
