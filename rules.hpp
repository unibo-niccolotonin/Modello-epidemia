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

/*
auto get_people_inside_radius(Board& board, int const& y, int const& x, int const& radius)
{
    std::vector<Cell> nearby_people; //Da sostituire con l'unique pointer
    for (int i = 0; i < (2 * radius + 1); i++)
    {
        for (int j = 0; j < (2 * radius + 1); j++)
        {
            //Da sostiruire con l'unique pointer
            auto person = board.get_person(y - radius + i, x - radius + j);

            if (person != NULL) nearby_people.push_back(person);
        }
    }
    auto central_person_iterator = std::find(nearby_people.begin(), nearby_people.end(), board.get_person(y, x));
    nearby_people.erase(central_person_iterator);
    return nearby_people;
}

//Pensare metodo di board che contiene le persone
void infection(Board& board)
{
    for (auto current_person : board.persons)
    {
        if (current_person.get_status == status::INFECTED)
        {
            auto nearby_people = get_people_inside_radius(board, current_person.get_y(), current_person.get_x(), infection_constants::radius);
            //Da completare

            for (auto infection_candidate : nearby_people)
            {
                // controllare che è veramente casuale
                std::random_device e;
                std::uniform_real_distribution<double> distribution(0,1);
                double random = distribution(e);
            }
        }
    }
}

void healing(Person& person)
{
    if()
}
*/

auto evolve(Board const& board)
{
    Board new_board = board;
    //infection
    for (int column = 0; row < board.size_(); row++)
    {
        for (int row = 0; column < board.size_(); column++)
        {
            Cell current_cell = board(column, row); 
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
                if (new_board(column, row).clock < infection_constants::infection_time)
                {
                    new_board(column, row).clock++;
                } 
                else 
                {
                    new_board(column, row).status = status::Immune; 
                }
            }
        }
    }


    return new_board;
}