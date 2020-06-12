#include <vector>
#include <random>
#include "board.hpp"
#include "board_functions.hpp"

namespace infection_constants
{
    int const radius = 1;
    float const infection_probability = 0.05;
    int const infection_time = 10;
    double mortality_rate = 0.2;
}

Board evolve(Board const& board)
{
    Board new_board = board;
    
    std::random_device e;
    std::uniform_real_distribution<double> distribution_for_probability(0, 1);
    std::uniform_int_distribution<int> velocity_distribution(-1, 1);
    
    for (int row = 0; row < board.get_size(); row++)
    {
        for (int column = 0; column < board.get_size(); column++)
        {
            Cell current_cell = board(row, column);
            
            //Cellule infette
            if (current_cell.status == state::infected)
            {
                
                //Infetta le altre cellule dentro il raggio
                for (int i = 0; i < (2 * infection_constants::radius + 1); i++)
                {
                    for (int j = 0; j < (2 * infection_constants::radius + 1); j++)
                    {
                        int coord_y = (row - infection_constants::radius) + i;
                        int coord_x = (column - infection_constants::radius) + j;

                        //if (coord_y >= 0 && coord_x >= 0 && coord_y < board.get_size() && coord_x < board.get_size())
                        //{
                            if (new_board(coord_y, coord_x).status == state::susceptible)
                            {
                                double random = distribution_for_probability(e);

                                if (random < infection_constants::infection_probability)
                                    new_board(coord_y, coord_x).status = state::infected;
                            }
                        //}
                    }
                }

                // Questo if else aumenta la variabile clock fino a un valore definito, dopodiché decide se la cellula diventa immune o muore
                if (new_board(row, column).clock < infection_constants::infection_time)
                {
                    new_board(row, column).clock++;
                }
                else
                {
                    double nrand = distribution_for_probability(e);
                    if (nrand <= infection_constants::mortality_rate)
                    {
                        new_board(row, column).status = state::dead;
                    }
                    else
                    {
                        new_board(row, column).status = state::immune;
                    }
                }
            }

            //Movimento delle cellule
            if ((current_cell.status != state::non_existant) && (current_cell.status != state::dead))
            {
                int failure_counter = 0;

                while (failure_counter != 1) // Se si mette un valore maggiore di uno il movimento appare più casuale. La performance del programma però ne risente quando ci sono molte cellule
                {
                    std::random_device e;

                    new_board(row, column).vx = velocity_distribution(e);
                    new_board(row, column).vy = velocity_distribution(e);

                    //Per leggibilità
                    int vx = new_board(row, column).vx;
                    int vy = new_board(row, column).vy;


                    //Ribalta la velocità della cellula se va fuori la griglia
                    if (row + vx >= new_board.get_size() || row + vx < 0)
                        vx = -vx;

                    if (column + vy >= new_board.get_size() || column + vy < 0)
                        vy = -vy;

                    if (new_board(row + vx, column + vy).status == state::non_existant)
                    {
                        new_board(row + vx, column + vy) = new_board(row, column);
                        new_board(row, column) = Cell(state::non_existant);

                        break;
                    }
                    failure_counter++;

                }

            }

        }
    }


    return new_board;
}
