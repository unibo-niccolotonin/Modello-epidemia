// Type your code here, or load an example.
#include <vector>
#include<iostream>

class Cell
{
    int n;
    bool state;
public:
    Cell(bool state_) : state{ state_ } {}

    bool statocellula();
};
bool Cell::statocellula()
{
    return state;
}

class Board
{
    bool st;
    int size;
    std::vector<std::vector<bool>> v1;
public:
    Board(int n) : size{ n }, v1(n, std::vector<bool>(n)) {}
    int size_() const { return size; }
};