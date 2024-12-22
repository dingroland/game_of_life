#ifndef CELLSTATE_H
#define CELLSTATE_H

enum class CellState { DEAD, ALIVE };

inline char cellToChar(CellState state) {
    return (state == CellState::ALIVE) ? 'x' : '.';
}

inline CellState charToCell(char ch) {
    return (ch == 'x') ? CellState::ALIVE : CellState::DEAD;
}

#endif
