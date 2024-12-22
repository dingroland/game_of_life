#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <vector>
#include <string>
#include "CellState.h"

class GameBoard {
public:
    GameBoard(int rows, int cols);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;
    void advanceGeneration();
    void printBoard() const;

private:
    int rows, cols;
    std::vector<std::vector<CellState>> grid;

    int countLiveNeighbors(int row, int col) const;
    int wrap(int value, int max) const;
};

#endif
