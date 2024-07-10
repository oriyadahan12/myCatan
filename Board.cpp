#include "Board.hpp"
#include "Plot.hpp"
#include "Player.hpp"
#include <vector>

using namespace std;

vector<vector<unsigned int>>SETTELMENTS_NEIGHBORS = {
        {3,4},{4,5},{5,6},{0,7},{0,1,8},{1,2,9},{2,10},{3,11,12},{4,12,13},{5,13,14},{6,14,15},{7,16},{7,8,17},{8,9,18},{9,10,19},{10,20},{11,21,22},{12,22,23},{13,23,24},{14,24,25},{14,24,25},{15,25,26},{16,27},{16,17,28},{17,18,29},{18,19,30},{19,20,31},{20,32},{21,33},{22,33,34},{23,34,35},{24,35,36},{25,36,37},{26,37},{27,28,38},{28,29,39},{29,30,40},{30,31,41},{31,32,42},{33,43},{34,43,44},{35,44,45},{36,45,46},{37,46},{38,39,47},{39,40,48},{40,41,49},{41,42,50},{43,51},{44,51,52},{45,52,53},{46,53},{47,48},{48,49},{49,50}
};
vector<vector<unsigned int>>SETTELMENTS_ROADS={
        {0,1},{2,3},{4,5},{0,6},{1,2,7},{3,4,8},{5,9},{6,10,11},{7,12,13},{8,14,15},{9,16,17},{10,18},{11,12,19},{13,14,20},{15,16,21},{17,22},{18,23,24},{19,25,26},{21,29,30},{22,31,32},{23,33},{24,25,34},{26,27,35},{28,29,36},{30,31,37},{32,38},{33,39},{34,40,41},{35,42,43},{30,48,49},{36,44,45},{37,46,47},{38,48},{39,40,49},{41,42,50},{43,44,51},{45,46,52},{47,48,53},{49,54},{50,55,56},{51,57,58},{52,59,60},{53,61},{54,55,62},{56,57,63},{58,59,64},{60,61,65},{62,66},{63,67,68},{64,69,70},{65,71},{66,77},{68,69},{70,71},{55,92,93},{56,94,95},{57,96,97},{58,98},{59,99},{60,61},{62,63},{64,65},{66,67},{68,69},{70,71}
};
const vector<vector<unsigned int>> SETTELEMENTS = {
        {0,4,8,12,7,3}, {1,5,9,13,8,4}, {2,6,10,14,9,5},
        {7,12,17,22,16,11}, {8,13,18,23,17,12}, {9,14,19,24,18,13}, {10,15,20,25,19,14},
        {16,22,28,33,27,21}, {17,23,29,34,28,22}, {18,24,30,35,29,23}, {19,25,31,36,30,24}, {20,26,32,37,31,25},
        {28,34,39,43,38,33}, {29,35,40,44,39,34}, {30,36,41,45,40,35}, {31,37,42,46,41,36},
        {39,44,48,51,47,43}, {40,45,49,52,48,44}, {41,46,50,53,49,45}
};

const vector<vector<unsigned int>> ROADS = {
        {1,7,12,11,6,0}, {3,8,14,13,7,2}, {5,9,16,15,8,4},
        {11,19,25,24,18,10}, {13,20,27,26,19,12}, {15,21,29,28,20,14}, {17,22,31,30,21,16},
        {24,34,40,39,33,23}, {26,35,42,41,34,25}, {28,36,44,43,35,27}, {30,37,46,45,36,29}, {32,38,48,47,37,31},
        {41,50,55,54,49,40}, {43,51,57,56,50,42}, {45,52,59,58,51,44}, {47,53,61,60,52,46},
        {56,63,67,66,62,55}, {58,64,69,68,63,57}, {60,65,71,70,64,59}
};

map<unsigned int, vector<unsigned int>>dice_results = {
        {2, {1}},
        {3, {10, 13}},
        {4, {5, 14}},
        {5, {15, 16}},
        {6, {4, 17}},
        {8, {11, 12}},
        {9, {7, 2}},
        {10, {0, 6}},
        {11, {18, 8}},
        {12, {3}}
};

void Board::produce(unsigned int dicenum){
    if(dicenum == 7 || dicenum < 2 || dicenum > 12){
        throw logic_error("Invalid dice number");
    }

    vector<unsigned int> plotsToProduce = dice_results.at(dicenum);
    for (unsigned int i = 0; i < plotsToProduce.size(); i++) {
        unsigned int curr = plotsToProduce[i];
        for (unsigned int j = 0; j < SETTELEMENTS[curr].size(); j++) {
            villages[SETTELEMENTS[curr][j]].receive(plots[curr].getType());
        }
    }

}
Board::Board(){
    initializePlots();
    roads.resize(72);
    villages.resize(54);
}

void Board::initializePlots() {
    plots.emplace_back(Resource::Brick);
    plots.emplace_back(Resource::Wood);
    plots.emplace_back(Resource::Iron);
    plots.emplace_back(Resource::Oats);
    plots.emplace_back(Resource::Brick);
    plots.emplace_back(Resource::Oats);
    plots.emplace_back(Resource::Wood);
    plots.emplace_back(Resource::Iron);
    plots.emplace_back(Resource::Wool);
    plots.emplace_back(Resource::None);
    plots.emplace_back(Resource::Wood);
    plots.emplace_back(Resource::Iron);
    plots.emplace_back(Resource::Oats);
    plots.emplace_back(Resource::Wool);
    plots.emplace_back(Resource::Brick);
    plots.emplace_back(Resource::Wood);
    plots.emplace_back(Resource::Oats);
    plots.emplace_back(Resource::Wool);
    plots.emplace_back(Resource::Wool);
}

void Board::buildRoad(Player& player, unsigned int roadIndex)
{
    if(canBuildRoad(player, roadIndex)){
        roads[roadIndex].build(player);
    }
    else{
        throw logic_error("Cannot build road");
    }
}

void Board::buildVillage(Player& player, unsigned int villageIndex, bool first){
    if(first){
        if(canBuildFirstVillage(player, villageIndex)){
            villages[villageIndex].build(player);
        }
        else{
            throw logic_error("Cannot build first village");
        }
    }
    else{
        if(canBuildVillage(player, villageIndex)){
            villages[villageIndex].build(player);
        }
        else{
            throw logic_error("Cannot build village");
        }
    }
}

void Board::upgradeVillage(Player& player, unsigned int villageIndex){
    if(canUpgradeVillage(player, villageIndex)){
        villages[villageIndex].upgrade();
    }
    else{
        throw logic_error("Cannot upgrade village");
    }

}

bool Board::canBuildRoad(Player& player, unsigned int roadIndex) const
{
    for(unsigned int i = 0; i < SETTELMENTS_ROADS.size(); i++)
    {
        for(unsigned int j = 0; j < SETTELMENTS_ROADS[i].size(); j++){
            if (SETTELMENTS_ROADS[i][j] == roadIndex) { // village i is connected to road j
                if (villages[i].isbuilt() && villages[i].getOwner() == &player)
                    return true;

                for (unsigned int k = 0; k < SETTELMENTS_ROADS[i].size(); k++) {
                    if (roads[SETTELMENTS_ROADS[i][k]].isBuilt() && roads[SETTELMENTS_ROADS[i][k]].getOwner() == &player)
                        return true;
                }
            }
        }
    }


    return false;
}

bool Board::canBuildVillage(Player& player, unsigned int villageIndex) const
{
    if (!canBuildFirstVillage(player, villageIndex)) return false;

    for(unsigned int i = 0; i < SETTELMENTS_ROADS[villageIndex].size(); i++)
    {
        if(roads[SETTELMENTS_ROADS[villageIndex][i]].isBuilt() && roads[SETTELMENTS_ROADS[villageIndex][i]].getOwner() == &player){
            return true;
        }
    }
    return false;

}

bool Board::canUpgradeVillage(Player& player, unsigned int villageIndex) const
{
    if(villages[villageIndex].isbuilt() == 1 && villages[villageIndex].getOwner() == &player){
        return true;
    }
    return false;
}

std::string Board::toString() const {
    for (unsigned int i = 0; i < 19; i++) {
        cout << i << ": " << plots[i].toString() << endl;
    }
    return std::string();
}

bool Board::canBuildFirstVillage(Player &player, unsigned int villageIndex) const {
    for(unsigned int i = 0; i < SETTELMENTS_NEIGHBORS[villageIndex].size(); i++)
    {
        if (villages[SETTELMENTS_NEIGHBORS[villageIndex][i]].isbuilt()){
            return false;
        }
    }
    return true;
}
