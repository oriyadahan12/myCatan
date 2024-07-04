#include "Player.hpp"

Player::Player(const std::string& name)
        : name(name), settlements(2), cities(0), roads(2), victoryPoints(2) {
    resources[Resource::Wood] = 0;
    resources[Resource::Brick] = 0;
    resources[Resource::Wool] = 0;
    resources[Resource::Oats] = 0;
    resources[Resource::Iron] = 0;
}

void Player::addResource(Resource resource, int amount) {
    resources[resource] += amount;
}

void Player::removeResource(Resource resource, int amount) {
    if (resources[resource] >= amount) {
        resources[resource] -= amount;
    }
}

int Player::getResourceCount(Resource resource) const {
    auto it = resources.find(resource);
    if (it != resources.end()) {
        return it->second;
    }
    return 0;
}

void Player::addSettlement(Plot& plot) {
    if (canBuildSettlement(plot)) {
        addResource(Resource::Wood, -1);
        addResource(Resource::Brick, -1);
        addResource(Resource::Wool, -1);
        addResource(Resource::Oats, -1);
        settlements++;
        calculateVictoryPoints();
        plot.setOwner(this); // Set the plot owner to this player
        ownedPlots.push_back(&plot); // Add plot to owned plots
    }
}

void Player::upgradeSettlementToCity(Plot& plot) {
    if (canBuildCity(plot)) {
        removeResource(Resource::Oats, -2);
        removeResource(Resource::Iron, -3);
        settlements--;
        cities++;
        calculateVictoryPoints();
        // Assuming plot has a method to indicate it has a city now
    }
}

void Player::addRoad() {
    if (canBuildRoad()) {
        addResource(Resource::Wood, -1);
        addResource(Resource::Brick, -1);
        roads++;
    }
}

bool Player::canBuildRoad() const {
    return getResourceCount(Resource::Wood) >= 1 && getResourceCount(Resource::Brick) >= 1;
}

bool Player::canBuildSettlement(Plot& plot) const {
    return getResourceCount(Resource::Wood) >= 1 && getResourceCount(Resource::Brick) >= 1 &&
           getResourceCount(Resource::Wool) >= 1 && getResourceCount(Resource::Oats) >= 1;
}

bool Player::canBuildCity(Plot& plot) const {
    return settlements > 0 && getResourceCount(Resource::Oats) >= 2 && getResourceCount(Resource::Iron) >= 3;
}

int Player::getVictoryPoints() const {
    return victoryPoints;
}

void Player::calculateVictoryPoints() {
    victoryPoints = settlements + 2 * cities;
}

void Player::addDevelopmentCard(const DevelopmentCard& card) {
    developmentCards.push_back(card);
}

void Player::useDevelopmentCard(int index) {
    if (index >= 0 && index < developmentCards.size()) {
        developmentCards.erase(developmentCards.begin() + index);
    }
}

void Player::initiateTrade(Player& otherPlayer,
                           const std::map<Resource, int>& offer,
                           const std::map<Resource, int>& request,
                           std::function<void(bool)> callback) {
    for (const auto& pair : offer) {
        if (getResourceCount(pair.first) < pair.second) {
            callback(false);
            return;
        }
    }
    otherPlayer.respondToTrade(*this, offer, request, callback);
}

void Player::respondToTrade(Player& initiator,
                            const std::map<Resource, int>& offer,
                            const std::map<Resource, int>& request,
                            std::function<void(bool)> callback) {
    bool accept = true; // Placeholder, actual logic to determine acceptance
    if (accept) {
        for (const auto& pair : request) {
            if (getResourceCount(pair.first) < pair.second) {
                callback(false);
                return;
            }
        }
        for (const auto& pair : offer) {
            removeResource(pair.first, pair.second);
            initiator.addResource(pair.first, pair.second);
        }
        for (const auto& pair : request) {
            addResource(pair.first, pair.second);
            initiator.removeResource(pair.first, pair.second);
        }
        calculateVictoryPoints();
        callback(true);
    } else {
        callback(false);
    }
}

void Player::playDevelopmentCard(int index, Player& target) {
    if (index >= 0 && index < developmentCards.size()) {
        DevelopmentCard& card = developmentCards[index];
        switch (card.getType()) {
            case DevelopmentCard::Type::Knight:
                // Implement Knight effect
                std::cout << "Using Knight card: Move the robber to a new location." << std::endl;
                // Example: Move the robber to a new location
                // target.moveRobber(newLocation);
                break;
            case DevelopmentCard::Type::VictoryPoint:
                // Implement Victory Point effect
                std::cout << "Using Victory Point card: Increase player's victory points." << std::endl;
                target.calculateVictoryPoints();
                break;
            case DevelopmentCard::Type::Promotion:
                // Implement Promotion effect based on promotion type
                switch (card.getPromotionType()) {
                    case DevelopmentCard::PromotionType::Monopoly:
                        // Implement Monopoly effect
                        std::cout << "Using Monopoly card: Implement Monopoly effect." << std::endl;
                        break;
                    case DevelopmentCard::PromotionType::RoadBuilding:
                        // Implement Road Building effect
                        std::cout << "Using Road Building card: Allow player to build two roads." << std::endl;
                        target.addRoad();
                        target.addRoad();
                        break;
                    case DevelopmentCard::PromotionType::YearOfPlenty:
                        // Implement Year of Plenty effect
                        std::cout << "Using Year of Plenty card: Implement Year of Plenty effect." << std::endl;
                        break;
                    default:
                        break;
                }
                break;
            default:
                // Handle other card types if needed
                break;
        }
        // Remove the used card from player's hand
        developmentCards.erase(developmentCards.begin() + index);
    }
}
std::string Player::getName() const {
    return name;
}
void Player::chooseInitialPlots(std::vector<Plot*>& availablePlots) {
    std::cout << "Player " << name << ", choose 2 plots for initial settlements:\n";
    for (int i = 0; i < 2; ++i) {
        int choice;
        std::cout << "Available plots:\n";
        for (size_t j = 0; j < availablePlots.size(); ++j) {
            std::cout << j + 1 << ". Plot number: " << availablePlots[j]->getNumber()
                      << ", Type: " << static_cast<int>(availablePlots[j]->getType()) << "\n";
        }
        std::cout << "Enter plot number for settlement " << i + 1 << ": ";
        std::cin >> choice;
        if (choice > 0 && choice <= availablePlots.size()) {
            addSettlement(*availablePlots[choice - 1]);
            availablePlots.erase(availablePlots.begin() + (choice - 1));
        } else {
            std::cout << "Invalid choice. Choose again.\n";
            --i; // Retry the current selection
        }
    }
}

void Player::printSettlements() const {
    std::cout << "Player " << name << "'s settlements:\n";
    for (const auto* plot : ownedPlots) {
        std::cout << "Plot number: " << plot->getNumber() << ", Type: " << static_cast<int>(plot->getType()) << "\n";
    }
}
