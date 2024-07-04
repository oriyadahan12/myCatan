#include "Board.hpp"
#include "Plot.hpp"
#include "Player.hpp"

Board::Board(int rows, int cols)
        : rows(rows), cols(cols) {
    initializePlots();
}

void Board::initializePlots() {
    plots.resize(rows);
    for (int i = 0; i < rows; ++i) {
        plots[i].resize(cols, Plot(Plot::Type::Desert, 0)); // Example initialization with default plot type
    }

    // Additional initialization logic based on your game's requirements
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            Plot::Type plotType = static_cast<Plot::Type>((i + j) % 6); // Example logic for alternating types
            int plotNumber = (i * cols + j + 1); // Example logic for assigning sequential numbers
            plots[i][j] = Plot(plotType, plotNumber);
        }
    }
}

void Board::placeInitialSettlements(std::vector<Player>& players) {
    // Example logic to place initial settlements for each player
    int playerIndex = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (playerIndex < players.size()) {
                plots[i][j].setOwner(&players[playerIndex]); // Setting owner of the plot
                players[playerIndex].addSettlement(plots[i][j]); // Example method on Player class
                playerIndex++;
            } else {
                return; // Exit if all players have placed their initial settlements
            }
        }
    }
}

Plot& Board::getPlot(int row, int col) {
    return plots[row][col];
}
