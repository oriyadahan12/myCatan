#ifndef DEVELOPMENT_CARD_H
#define DEVELOPMENT_CARD_H

#include <string>
#include <iostream>
#include <memory>
#include "Resource.hpp"

class Game;
class Player;
using namespace std;

class DevelopmentCard {
public:
    virtual ~DevelopmentCard() = default;
    virtual std::string toString() const = 0;
    virtual void play(Player&, Game&) = 0;//function without implementation.
};

class KnightCard : public DevelopmentCard {
    virtual std::string toString() const override
    {
        return "Knight Card";
    }

    virtual void play(Player& player, Game& game) override;

};

class MonopolyCard : public DevelopmentCard {
    virtual std::string toString() const override
    {
            return "Monopoly Card";
    }

    void play(Player& player, Game& game) override;
};

class PointsCard : public DevelopmentCard {
    virtual std::string toString() const override
    {
        return "Points Card";
    }

     void play(Player& player, Game& game) override;
};

class RoadsCard : public DevelopmentCard {
    virtual std::string toString() const override
    {
        return "Roads Card";
    }

     void play(Player& player, Game& game) override;
};

class YearOfPlentyCard : public DevelopmentCard {
    virtual std::string toString() const override
    {
        return "Year of plenty Card";
    }

    void play(Player& player, Game& game) override ;

};

#endif // DEVELOPMENT_CARD_H
