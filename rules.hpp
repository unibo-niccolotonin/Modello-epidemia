#pragma once
#include "board.hpp"
#include <vector>
#include <random>

namespace infection_constants
{
    const int radius = 1;
    const double infection_probability = 0.1;
}

auto check_radius(Board& board, int y, int x, int radius)
{
    std::vector<Person*> nearby_people; //Da sostituire con l'unique pointer

    for (int i = 0; i < (2 * radius + 1); i++)
    {
        for (int j = 0; j < (2 * radius + 1); j++)
        {
            //Da sostiruire con l'unique pointer
            auto person = std::vector<Person*> = board.get_person(y - radius + i, x - radius + j);

            if (person != NULL) nearby_people.push_back(person);
        }
    }

    return nearby_people;
}

//Pensare metodo di board che contiene le persone
void infection(Board& board, std::vector<Person> &persons)
{
    for (auto current_person : persons)
    {
        if (a.get_status == status::INFECTED)
        {
            auto nearby_people = check_radius(board, current_person.get_x(), current_person.get_y(), infection_constants::radius);
            //Da completare
        }
    }
}

void healing()
{
    
}

void evolve(Board& board)
{
    
}