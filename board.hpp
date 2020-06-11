#pragma once
#include <vector>
#include <iostream>
#include <cassert>

enum state { susceptible, dead, immune, non_existant, infected };
class Cell
{
public:
    int Vx, Vy;
    int clock;
    state status;
    Cell(state stato) : Vx(0), Vy(0), clock(0), status(stato) {};
};

class Board
{
    int size;
    std::vector<std::vector<Cell> > board_;
public:
    Board(int n) : cell_length(5.0f), graph_height(100.0f), graph_column_width(2.0f), size(n), board_(n, std::vector<Cell>(n, Cell(state::non_existant))) {};
    
    float cell_length;
    float graph_height;
    float graph_column_width;
        
    int get_size() const { return size; }
    bool insertCell(int r, int c);
    bool insertCell(int r, int c, state statocellula);
    
    Cell& operator()(int x, int y);

    Cell operator()(int x, int y) const;

};
