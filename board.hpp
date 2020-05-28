// Type your code here, or load an example.
#include <vector>
#include<iostream>
enum state { susceptible, dead, immune, non_existant, infected };
class Cell
{
    int n;
public:
    int Vx, Vy;
    state status;
    Cell(state stato) : status{ stato } {};
};




class Board
{
    int size;
    std::vector<std::vector<Cell>> board_;
public:

    Board(int n) : size{ n }, board_(n, std::vector<Cell>(n, Cell(state::non_existant))) {};
    int get_size() const { return size; }
    bool insertCell(int r, int c);

    Cell& operator()(int x, int y)
    {
        assert(x >= 0 && x < size&& y >= 0 && y < size);
        return board_[x][y];
    }

    Cell operator()(int x, int y) const
    {
        assert(x >= 0 && x < size&& y >= 0 && y < size);
        return board_[x][y];
    }

};

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
}