#ifndef DEVELOPMENT_CARD_H
#define DEVELOPMENT_CARD_H

#include <string>

class Game;
class Player;

class DevelopmentCard {
public:
    virtual void play(Player&, Game&) = 0;//function without implementation.

};

#endif // DEVELOPMENT_CARD_H
