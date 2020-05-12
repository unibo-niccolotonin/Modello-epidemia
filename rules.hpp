#pragma once
#include "board.hpp"
#include <vector>
#include <random>

namespace infection_constants
{
    const int radius = 1;
    const double infection_probability = 0.1;
    const int infection_time = 30;
}

auto evolve(Board const& board)
{
    Board new_board = board;
    
    for (int row = 0; row < board.size_(); row++)
    {
        for (int column = 0; column < board.size_(); column++)
        {
            Cell current_cell = board(row, column); 

            //infection
            if (current_cell.status == state::infected)
            {
                //Infect other cells
                for (int i = 0; i < (2 * infection_constants::radius + 1; i++)
                {
                    for (int j = 0; i < (2 * infection_constants::radius + 1); i++)
                    {
                        if (new_board(i, j).state == state::Susceptible)
                        {
                            // controllare che è veramente casuale
                            std::random_device e;
                            std::uniform_real_distribution<double> distribution(0,1);
                            double random = distribution(e);

                            if (random < infection_constants::infection_probability)
                                new_board(i, j).state = state::infected;
                        }
                    }
                }

                // Clock progression
                if (new_board(row, column).clock < infection_constants::infection_time) //Change time to a variable
                {
                    new_board(row, column).clock++;
                } 
                else 
                {
                    new_board(row, column).state = state::immune; 
                }
            }

            //movement
            //NOTA: occorre dare la possibilità di scegliere quale utilizzare
            if (current_cell.status != state::non_existant)
            {
                int failure_counter = 0;
                while (failure_counter != 8)
                {
                std::random_device a;
                std::random_device b;
                std::uniform_real_distribution<int> distribution(0,1); //La distribuzione potrebbe essere cambiata e riflettere della dimensione della board
                new_board(row, column).vx = distribution(a);
                new_board(row, column).vy = distribution(b);
                
                //for readability
                int vx = &new_board(row, column).vx;
                int vy = &new_board(row, column).vy;
                

                //Boundary conditions
                if (row + vx > new_board.size_() || row + vx < 0)
                    vx = -vx;

                if (column + vy > new_board.size_() || column + vy < 0 )
                    vy -vy;

                if (new_board(row + vx, column + vy).state == state::non_existant)
                {
                    new_board(row + vx, column + vy) = new_board(row, column);
                    new_board(row, column) = Cell(state::non_existant); // Assicurarsi che funzioni questa riassegnazione

                    break;
                }
                failure_counter++;

                }
            }

        }
    }


    return new_board;
}