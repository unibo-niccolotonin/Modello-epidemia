#include <iostream>
#include "board.hpp"
#include "rules.hpp"

int main()
{
    Board board(20);

    board.insertCell(4, 5);

    board = evolve(board);

    return 0;
}