#include "Player.hpp"

using namespace std;

Player::Player(const std::string& name)
        : name(name), victoryPoints(0) {
    // Initialize all resources to zero initially
    resources[Resource::Wood] = 0;
    resources[Resource::Brick] = 0;
    resources[Resource::Wool] = 0;
    resources[Resource::Oats] = 0;
    resources[Resource::Iron] = 0;
}

void Player::addResource(Resource resource, unsigned int amount) {
    if (resources.find(resource) == resources.end())
        resources[resource] = 0;
    resources[resource] += amount;
}


unsigned int Player::getResourceCount(Resource resource) const {
    return resources.at(resource);
}


bool Player::canAfford(std::map<Resource, unsigned int> price) const {
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

void Player::loseResource(Resource r, unsigned int amount) {
    resources[r] -= amount;
}

void Player::addDevelopmentCard(string str) {
    if (developmentCards.find(str) != developmentCards.end()) {
        developmentCards[str]++;
    } else {
        developmentCards[str] = 1;
    }
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
    if (developmentCards.find(str) == developmentCards.end() || developmentCards[str] == 0) {
        delete card;
        throw std::logic_error("Player does not have this card");
    }

    card->play(*this, game);
    developmentCards[str]--;
    delete card;
}

void Player::removeCard(string str) {
    if (developmentCards.find(str) == developmentCards.end() || developmentCards[str] == 0) {
        throw std::logic_error("Player does not have this card");
    }
    developmentCards[str]--;
}

unsigned int Player::numCards(std::string str) const {
    if (developmentCards.find(str) == developmentCards.end()) {
        return 0;
    }
    return developmentCards.at(str);
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
        cout << pair.first << ": " << pair.second << endl;
    }
}
