#include "board.hpp"
#include <cassert>
#include <iostream>
#include <vector>

Cell Board::m_null_cell = Cell(NON_EXISTANT);

bool Board::insertCell(int r, int c) {
  if (r >= 0 && c >= 0 && r < size && c < size) {
    if (board_[r][c].status == NON_EXISTANT) {
      board_[r][c].status = SUSCEPTIBLE;
      return true;
    } else
      return false;
  } else
    return false;
};

bool Board::insertCell(int r, int c, state statocellula) {
  if (r >= 0 && c >= 0 && r < size && c < size) {
    if (board_[r][c].status == NON_EXISTANT) {
      board_[r][c].status = statocellula;
      return true;
    } else
      return false;
  } else
    return false;
}

Cell &Board::operator()(int y, int x) {
  // assert(x >= 0 && x < size&& y >= 0 && y < size);
  if (x >= 0 && x < size && y >= 0 && y < size) {
    return board_[y][x];
  } else
    return m_null_cell;
}

Cell Board::operator()(int y, int x) const {
  if (x >= 0 && x < size && y >= 0 && y < size) {
    return board_[y][x];
  } else
    return Cell(NON_EXISTANT);
}
