#ifndef DEVELOPMENT_CARD_H
#define DEVELOPMENT_CARD_H

#include <string>

class DevelopmentCard {
public:
    enum class Type {
        Promotion,
        Knight,
        VictoryPoint
    };

    enum class PromotionType {
        Monopoly,
        RoadBuilding,
        YearOfPlenty
    };

    DevelopmentCard(Type type);
    DevelopmentCard(PromotionType promotionType);

    Type getType() const;
    PromotionType getPromotionType() const;
    std::string toString() const;

private:
    Type type;
    PromotionType promotionType;
    bool isPromotion;

    std::string typeToString() const;
    std::string promotionTypeToString() const;
};

#endif // DEVELOPMENT_CARD_H
