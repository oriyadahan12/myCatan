#include "development_card.hpp"

DevelopmentCard::DevelopmentCard(Type type) : type(type), isPromotion(false) {}

DevelopmentCard::DevelopmentCard(PromotionType promotionType)
        : type(Type::Promotion), promotionType(promotionType), isPromotion(true) {}

DevelopmentCard::Type DevelopmentCard::getType() const {
    return type;
}

DevelopmentCard::PromotionType DevelopmentCard::getPromotionType() const {
    return promotionType;
}

std::string DevelopmentCard::toString() const {
    if (isPromotion) {
        return promotionTypeToString();
    }
    return typeToString();
}

std::string DevelopmentCard::typeToString() const {
    switch (type) {
        case Type::Promotion: return "Promotion";
        case Type::Knight: return "Knight";
        case Type::VictoryPoint: return "Victory Point";
        default: return "Unknown";
    }
}

std::string DevelopmentCard::promotionTypeToString() const {
    switch (promotionType) {
        case PromotionType::Monopoly: return "Monopoly";
        case PromotionType::RoadBuilding: return "Road Building";
        case PromotionType::YearOfPlenty: return "Year Of Plenty";
        default: return "Unknown";
    }
}
