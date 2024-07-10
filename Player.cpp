#include "Player.hpp"

using namespace std;
Player::Player(const std::string& name)
        : name(name), victoryPoints(2) {
    resources[Resource::Wood] = 0;
    resources[Resource::Brick] = 0;
    resources[Resource::Wool] = 0;
    resources[Resource::Oats] = 0;
    resources[Resource::Iron] = 0;
}

void Player::addResource(Resource resource, unsigned int amount) {
    std::cout << "Adding " << amount << " " << resourceToString(resource) << " to " << name << std::endl;
    if (resources.find(resource) == resources.end())
        resources[resource] = 0;
    std::cout << "Before " << std::endl;
    resources[resource] += amount;
    std::cout << "After " << std::endl;
}

void Player::removeResource(Resource resource, unsigned int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
    }
    else{
        throw std::logic_error("Not enough resources to remove");
    }
}

unsigned int Player::getResourceCount(Resource resource) const {
   return resources.at(resource);
}


bool Player::canAfford(map<Resource, unsigned int>price) const {
    for (const auto& pair : price) {
        if (resources.at(pair.first) < pair.second) {
            return false;
        }
    }
    return true;
}

void Player::pay(std::map<Resource, unsigned int> price) {
    if (!canAfford(price))
        throw logic_error("Can't afford");

    for (const auto& pair : price) {
        resources[pair.first] -= pair.second;
    }
}

void Player::receive(std::map<Resource, unsigned int> price) {
    for (const auto& pair : price) {
        resources[pair.first] += pair.second;
    }
}

unsigned int Player::getVictoryPoints() const {
    return victoryPoints;
}

std::string Player::getName() const {
    return name;
}

unsigned int Player::sumResources() const {
    unsigned int sum = 0;
    for (const auto& pair : resources) {
        sum += pair.second;
    }
    return sum;
}

void Player::loseHalfResources() {
    for (const auto& pair : resources) {
        resources[pair.first] /= 2;
    }
}

void Player::loseResource(Resource r) {
    resources[r] = 0;
}

void Player::addDevelopmentCard(DevelopmentCard* card) {
    if(developmentCards.find(card) != developmentCards.end())
        developmentCards[card]++;
    else
        developmentCards[card] = 1;
}

DevelopmentCard* stringToCard(string str) {
    if (str == "Knight") {
        return new KnightCard();
    } else if (str == "Monopoly") {
        return new MonopolyCard();
    } else if (str == "Points") {
        return new PointsCard();
    } else if (str == "Roads") {
        return new RoadsCard();
    } else if (str == "Year of plenty") {
        return new YearOfPlentyCard();
    }
    return nullptr;
}

void Player::playDevelopmentCard(string str, Game& game) {
    DevelopmentCard* card = stringToCard(str);
    if (developmentCards.find(card) == developmentCards.end() || developmentCards[card] == 0) {
        delete card;
        throw std::logic_error("Player does not have this card");
    }

    card->play(*this, game);
    developmentCards[card]--;
    delete card;
}

void Player::removeCard(string str){
    DevelopmentCard* card = stringToCard(str);
    if (developmentCards.find(card) == developmentCards.end() || developmentCards[card] == 0) {
        delete card;
        throw std::logic_error("Player does not have this card");
    }

    developmentCards[card]--;
    delete card;
}

unsigned int Player::numCards(std::string str) const {
    DevelopmentCard* card = stringToCard(str);
    if (developmentCards.find(card) == developmentCards.end()) {
        delete card;
        return 0;
    }

    delete card;
    return developmentCards.at(card);
}

void Player::printResources() const {
    cout << "Resources:" << endl;
    for (const auto& pair : resources) {
        cout << resourceToString(pair.first) << ": " << pair.second << endl;
    }
}

void Player::printCards() const {
    cout << "Development Cards:" << endl;
    for (const auto& pair : developmentCards) {
        cout << pair.first->toString() << ": " << pair.second << endl;
    }
}
