#include <vector>
#include <random>
#include "board.hpp"
#include "board_functions.hpp"

namespace infection_constants
{
    int const radius = 1;
    float const infection_probability = 0.2;
    int const infection_time = 10;
    double mortality_rate = 0.2;
    } // namespace infection_constants

Board evolve(Board const& board)
{
    Board new_board = board;
    
    std::random_device device;
    std::uniform_real_distribution<double> distribution_for_probability(0, 1);
    std::uniform_int_distribution<int> velocity_distribution(-1, 1);
    
    for (int row = 0; row < board.get_size(); row++)
    {
        for (int column = 0; column < board.get_size(); column++)
        {
            Cell current_cell = board(row, column);
            
            //Comportamento delle cellule infette
            if (current_cell.status == INFECTED)
            {
                
                //Infetta le altre cellule dentro il raggio
                for (int i = 0; i < (2 * infection_constants::radius + 1); i++)
                {
                    for (int j = 0; j < (2 * infection_constants::radius + 1); j++)
                    {
                        int coord_y = (row - infection_constants::radius) + i;
                        int coord_x = (column - infection_constants::radius) + j;


                        if (new_board(coord_y, coord_x).status == SUSCEPTIBLE)
                        {
                            double random = distribution_for_probability(device);

                            if (random < infection_constants::infection_probability)
                                new_board(coord_y, coord_x).status = INFECTED;
                        }
                }
                }

                // Questo if else aumenta la variabile clock fino a un valore definito, dopodiché decide se la cellula diventa immune o muore
                if (new_board(row, column).clock < infection_constants::infection_time)
                {
                    new_board(row, column).clock++;
                }
                else
                {
                    double nrand = distribution_for_probability(device);
                    if (nrand <= infection_constants::mortality_rate)
                    {
                        new_board(row, column).status = DEAD;
                    }
                    else
                    {
                        new_board(row, column).status = IMMUNE;
                    }
                }
            }
        }
    }
    
    /* Abbiamo deciso di mettere il processo di infezione device quello di movimento in for loops separati per diminuire il bias verso le cellule in alto a sinistra che vengono valutate per prima. A dir la verità il bias non si nota se il valore massimo della velocità è basso. In caso contrario però, si può notare che mediamente il numero di cellule mai infettate è più alto. La nostra ipotesi è che questo è causato in quanto esse hanno più probabilità di allontanarsi dal blocco principale di cellule quando vengono inserite inizialmente. Non abbiamo rivelato un consumo della performance significativo aggiungendo i for loops per il movimento, dunque li abbiamo inclusi */
    
    //Movimento delle cellule
    
    for (int row = 0; row < board.get_size(); row++)
    {
        for (int column = 0; column < board.get_size(); column++)
        {
            Cell current_cell = board(row, column);
    
            if ((current_cell.status != NON_EXISTANT) && (current_cell.status != DEAD))
            {
                int failure_counter = 0;

                while (failure_counter != 1) // Se si mette un valore maggiore di uno il movimento appare più casuale. La performance del programma però ne risente quando ci sono molte cellule
                {
                    std::random_device device;

                    new_board(row, column).vx = velocity_distribution(device);
                    new_board(row, column).vy = velocity_distribution(device);

                    int vx = new_board(row, column).vx;
                    int vy = new_board(row, column).vy;


                    //Ribalta la velocità della cellula se va fuori la griglia
                    if (column + vx >= new_board.get_size() || column + vx < 0)
                        vx = -vx;

                    if (row + vy >= new_board.get_size() || row + vy < 0)
                        vy = -vy;

                    if (new_board(row + vy, column + vx).status == NON_EXISTANT)
                    {
                        new_board(row + vy, column + vx) = new_board(row, column);
                        new_board(row, column) = Cell(NON_EXISTANT);

                        break;
                    }
                    failure_counter++;

                }

            }

        }
    }
    


    return new_board;
}
