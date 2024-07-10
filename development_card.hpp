#ifndef DEVELOPMENT_CARD_H
#define DEVELOPMENT_CARD_H

#include <string>
#include <iostream>
#include <memory>
#include "Resource.hpp"

class Game;
class Player;

using namespace std;

/**
 * @brief Abstract base class for Development Cards.
 */
class DevelopmentCard {
public:
    virtual ~DevelopmentCard() = default;

    /**
     * @brief Returns a string representation of the card.
     */
    virtual std::string toString() const = 0;

    /**
     * @brief Performs the action associated with playing the card.
     */
    virtual void play(Player& player, Game& game) = 0;
};

/**
 * @brief Concrete class representing a Knight card.
 */
class KnightCard : public DevelopmentCard {
public:
    virtual std::string toString() const override {
        return "Knight";
    }

    virtual void play(Player& player, Game& game) override;
};

/**
 * @brief Concrete class representing a Monopoly card.
 */
class MonopolyCard : public DevelopmentCard {
public:
    virtual std::string toString() const override {
        return "Monopoly";
    }

    virtual void play(Player& player, Game& game) override;
};

/**
 * @brief Concrete class representing a Points card.
 */
class PointsCard : public DevelopmentCard {
public:
    virtual std::string toString() const override {
        return "Points";
    }

    virtual void play(Player& player, Game& game) override;
};

/**
 * @brief Concrete class representing a Roads card.
 */
class RoadsCard : public DevelopmentCard {
public:
    virtual std::string toString() const override {
        return "Roads";
    }

    virtual void play(Player& player, Game& game) override;
};

/**
 * @brief Concrete class representing a Year of Plenty card.
 */
class YearOfPlentyCard : public DevelopmentCard {
public:
    virtual std::string toString() const override {
        return "Year of plenty";
    }

    virtual void play(Player& player, Game& game) override;
};

#endif // DEVELOPMENT_CARD_H
