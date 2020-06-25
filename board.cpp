#include "board.hpp"
#include <cassert>
#include <iostream>
#include <vector>
#include <random>

float Board::infection_probability = 0.2;
int Board::infection_radius = 1 ;
int Board::infection_time = 30;
float Board::mortality_rate = 0.3;

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

void Board::fill_board(int n)
{
  assert (n < size_ * size_);

  std::random_device rd;
  std::mt19937 dev(rd());
  std::uniform_int_distribution<int> random_coord(0, size_ - 1);

  int i = 0;
  while (i < n)
  {
    int coord_x = random_coord(dev);
    int coord_y = random_coord(dev);

    if (board_[coord_y * size_ + coord_x].status == NON_EXISTANT)
    {
      this->insertCell(coord_y, coord_x);
      i++;
    }
  }
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
