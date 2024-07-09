//
// .
//

#ifndef NEWCATAN_VILLAGE_HPP
#define NEWCATAN_VILLAGE_HPP

#include "Player.hpp"
class Village {

    Player* owner;
    enum class Type : unsigned int {
        None = 0,
        Settlement = 1,
        City = 2
    };
    Type type;

public:
    void build(Player& player);
    void upgrade();
    void receive(Resource r);
    unsigned int isbuilt()const{return (unsigned int) type;};
    Player* getOwner() const {return owner;}
    Village(): type(Type::None) {}
};


#endif //NEWCATAN_VILLAGE_HPP
