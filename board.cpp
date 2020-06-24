#include "board.hpp"
#include <cassert>
#include <iostream>
#include <vector>

Cell Board::null_cell_ = Cell(NON_EXISTANT);

bool Board::insertCell(int r, int c) 
{
  if (r >= 0 && c >= 0 && r < size_ && c < size_) 
  {
    if (board_[r * size_ + c].status == NON_EXISTANT) 
    {
      board_[r * size_ + c].status = SUSCEPTIBLE;
      return true;
    }
  }
  return false;
};

bool Board::insertCell(int r, int c, state cell_state) 
{
  if (r >= 0 && c >= 0 && r < size_ && c < size_) 
  {
    if (board_[r * size_ + c].status == NON_EXISTANT) 
    {
      board_[r * size_ + c].status = cell_state;
      return true;
    } else
      return false;
  } else
    return false;
}

Cell &Board::operator()(int y, int x) 
{
  if (x >= 0 && x < size_ && y >= 0 && y < size_) 
  {
    return board_[y * size_ + x];
  } else
    return null_cell_;
}

Cell Board::operator()(int y, int x) const 
{
  if (x >= 0 && x < size_ && y >= 0 && y < size_) 
  {
    return board_[y * size_ + x];
  } else
    return Cell(NON_EXISTANT);
}
