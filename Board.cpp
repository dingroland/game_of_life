#include "Board.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

GameBoard::GameBoard(int rows, int cols) : rows(rows), cols(cols), grid(rows, std::vector<CellState>(cols, CellState::DEAD)) {}

void GameBoard::loadFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    infile >> rows;
    infile.ignore(1);  // Skip the comma
    infile >> cols;

    grid.resize(rows, std::vector<CellState>(cols, CellState::DEAD));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            char ch;
            infile >> ch;
            grid[i][j] = charToCell(ch);
        }
    }

    infile.close();
}

void GameBoard::saveToFile(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }

    outfile << rows << "," << cols << "\n";
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            outfile << cellToChar(grid[i][j]);
        }
        outfile << "\n";
    }

    outfile.close();
}

void GameBoard::advanceGeneration() {
    std::vector<std::vector<CellState>> nextGrid = grid;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = countLiveNeighbors(i, j);

            if (grid[i][j] == CellState::ALIVE) {
                nextGrid[i][j] = (liveNeighbors == 2 || liveNeighbors == 3) ? CellState::ALIVE : CellState::DEAD;
            } else {
                nextGrid[i][j] = (liveNeighbors == 3) ? CellState::ALIVE : CellState::DEAD;
            }

            // Debugging: Print cell state transitions
            std::cout << "Cell (" << i << "," << j << "): "
                      << cellToChar(grid[i][j]) << " -> "
                      << cellToChar(nextGrid[i][j])
                      << " (Live Neighbors: " << liveNeighbors << ")\n";
        }
    }

    grid = nextGrid;

    // Debugging: Print the grid after every generation
    std::cout << "Generation Complete:\n";
    printBoard();
    std::cout << std::string(20, '-') << "\n";  // Separator for readability
}


int GameBoard::countLiveNeighbors(int row, int col) const {
    int liveCount = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0) {
                int ni = wrap(row + i, rows);
                int nj = wrap(col + j, cols);
                if (grid[ni][nj] == CellState::ALIVE) {
                    liveCount++;
                }
            }
        }
    }
    return liveCount;
}

int GameBoard::wrap(int value, int max) const {
    return (value + max) % max;
}

void GameBoard::printBoard() const {
    for (const auto& row : grid) {
        for (const auto& cell : row) {
            std::cout << cellToChar(cell);
        }
        std::cout << "\n";
    }
}
