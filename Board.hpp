#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Plot.hpp"
#include "Player.hpp" // Include Player class for reference

class Board {
public:
    Board(int rows, int cols); // Constructor with parameters

    void initializePlots(); // Initialization method for the plots
    void placeInitialSettlements(std::vector<Player>& players); // Declaration of the method
    Plot& getPlot(int row, int col); // Method to get a specific plot

private:
    int rows;
    int cols;
    std::vector<std::vector<Plot>> plots;
};

#endif // BOARD_HPP
