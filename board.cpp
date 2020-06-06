#include "board.hpp"
#include <vector>
#include <iostream>
#include <cassert>

bool Board::insertCell(int r, int c)
{
    if (r >= 0 && c >= 0 && r < size && c < size)
    {
        if (board_[r][c].status == state::non_existant)
        {
            board_[r][c].status = state::susceptible;
            return true;
        }
        else
            return false;
    }
    else
        return false;
};

bool Board::insertCell(int r, int c, state statocellula)
{
    if (r >= 0 && c >= 0 && r < size && c < size)
    {
        if (board_[r][c].status == state::non_existant)
        {
            board_[r][c].status = statocellula;
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

Cell& Board::operator()(int x, int y)
    {
        assert(x >= 0 && x < size&& y >= 0 && y < size);
        return board_[x][y];
    }

Cell Board::operator()(int x, int y) const
    {
        assert(x >= 0 && x < size&& y >= 0 && y < size);
        return board_[x][y];
    }