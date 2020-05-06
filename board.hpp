// Type your code here, or load an example.
#include <vector>
#include<iostream>
class Cell
{
    int n;
public:
    enum state { alive, dead, immune, non_existant };
    int Vx, Vy;
    int l, c; //coordinate
};

//elPsyKongroo
class Board
{
    int size;
    std::vector<std::vector<Cell>> board_;
public:
    Board(int n) : size{ n }, board_(n, std::vector<Cell>(n, state::non_existant)) {}
    int size_() const { return size; }
    state insertCell(int r, int c);
};

state Board::insertCell(int r, int c)
{
    if (r < size && c < size)
    {
        if (state::non_existant)
        {
            return state::alive;
        }
        if (state::dead)
        {
            return state::alive;
        }
        if (state::alive)
        {
            state::non_existant;
        }
    }
    else
    {
        return state::non_existant;
    }
}
int main()
{
    int dim;
    dim = 10;
    Board board(dim);
}