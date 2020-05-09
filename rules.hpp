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
    
    for (int column = 0; row < board.size_(); row++)
    {
        for (int row = 0; column < board.size_(); column++)
        {
            Cell current_cell = board(column, row); 

            //infection
            if (current_cell.status == status::Infected)
            {
                //Infect other cells
                for (int i = 0; i < (2 * infection_constants:radius + 1; i++)
                {
                    for (int j = 0; i < (2 * infection_constants:radius + 1); i++)
                    {
                        if (new_board(i, j).status == status::Susceptible)
                        {
                            // controllare che è veramente casuale
                            std::random_device e;
                            std::uniform_real_distribution<double> distribution(0,1);
                            double random = distribution(e);

                            if (random < infection_constants::infection_probability)
                                new_board(i, j).status = status::Infected;
                        }
                    }
                }

                // Clock progression
                if (new_board(column, row).clock < infection_constants::infection_time) //Change time to a variable
                {
                    new_board(column, row).clock++;
                } 
                else 
                {
                    new_board(column, row).status = status::Immune; 
                }
            }

            //movement
            //NOTA: occorre dare la possibilità di scegliere quale utilizzare
            if (current_cell.status != status::Non_existant)
            {
                int failure_counter = 0;
                while (failure_counter != 8)
                {
                std::random_device a;
                std::random_device b;
                std::uniform_real_distribution<int> distribution(0,1); //La distribuzione potrebbe essere cambiata
                new_board(column, row).vx = distribution(a);
                new_board(column, row).vy = distribution(b);

                //for readability
                int vx = &new_board(column, row).vx;
                int vy = &new_board(column, row).vy;
                
                if (new_board(column + vy, row + vx).status == status::Non_existant)
                {
                    new_board(column + vy, row + vx) = new_board(column, row);
                    new_board(column, row) = Cell(); // Assicurarsi che funzioni questa riassegnazione

                    break;
                }
                failure_counter++;

                }
            }

        }
    }


    return new_board;
}