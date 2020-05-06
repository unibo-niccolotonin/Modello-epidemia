// Type your code here, or load an example.
#include <vector>
#include<iostream>
enum state { alive, dead, immune, non_existant, infected };
class Cell
{
    int n;
public:
    int Vx, Vy;
    state status;
    Cell(state stato) : status{ stato } {}
};


class Board
{
    int size;
    std::vector<std::vector<Cell>> board_;
public:

    Board(int n) : size{ n }, board_(n, std::vector<Cell>(n, Cell(non_existant))) {}
    int size_() const { return size; }
    bool insertCell(int r, int c);
};

bool Board::insertCell(int r, int c)
{
    if (r < size && c < size)
    {
        if (board_[r][c].status == non_existant)
        {
            board_[r][c].status == alive;
            return true;
        }
        else
            return false;
    }
}
int main()
{
    int dim;
    dim = 10;
    Board board(dim);
}