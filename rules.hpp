#pragma once
#include "board.hpp"
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

namespace infection_constants
{
    int const radius = 1;
    float const infection_probability = 0.1;
    int const infection_time = 30;
}

Board evolve(Board const& board)
{
    Board new_board = board;
    
    for (int row = 0; row < board.get_size(); row++)
    {
        for (int column = 0; column < board.get_size(); column++)
        {
            Cell current_cell = board(row, column); 

            //infection
            if (current_cell.status == state::infected)
            {
                //Infect other cells
                for (int i = 0; i < (2 * infection_constants::radius + 1); i++)
                {
                    for (int j = 0; i < (2 * infection_constants::radius + 1); i++)
                    {
                      int coord_x = (row - infection_constants::radius) + i;
                      int coord_y = (column - infection_constants::radius) + j;
                      
                      if (coord_x >= 0 && coord_y >= 0 && coord_x < board.get_size() && coord_y < board.get_size())
                      {
                        if (new_board(coord_x, coord_y).status == state::susceptible)
                        {
                            // controllare che è veramente casuale
                            std::random_device e;
                            std::uniform_real_distribution<double> distribution(0,1);
                            double random = distribution(e);

                            if (random < infection_constants::infection_probability)
                                new_board(coord_x, coord_y).status = state::infected;
                        }
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
                    new_board(row, column).status = state::immune; 
                }
            }

            //movement
            //NOTA: occorre dare la possibilità di scegliere quale utilizzare
            if (current_cell.status != state::non_existant)
            {
                int failure_counter = 0;
                while (failure_counter != 8)
                {
                    srand(time(0)); // Questo risolve il problema però non è veramente random
                
                    new_board(row, column).Vx = (rand() % 2);
                    new_board(row, column).Vy = (rand() % 2);
                
                //for readability
                int vx = new_board(row, column).Vx;
                int vy = new_board(row, column).Vy;
                

                //Boundary conditions
                if (row + vx > new_board.get_size() || row + vx < 0)
                    vx = -vx;

                if (column + vy > new_board.get_size() || column + vy < 0 )
                    vy = -vy;

                if (new_board(row + vx, column + vy).status == state::non_existant)
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
