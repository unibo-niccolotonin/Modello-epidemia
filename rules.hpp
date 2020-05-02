#pragma once
#include "board.hpp"
#include <vector>
#include <random>

namespace infection_constants
{
    const int radius = 1;
    const double infection_probability = 0.1;
}

auto get_people_inside_radius(Board& board, int const& y, int const& x, int const& radius)
{
    std::vector<Person> nearby_people; //Da sostituire con l'unique pointer
    for (int i = 0; i < (2 * radius + 1); i++)
    {
        for (int j = 0; j < (2 * radius + 1); j++)
        {
            //Da sostiruire con l'unique pointer
            auto person = std::vector<Person*> = board.get_person(y - radius + i, x - radius + j);

            if (person != NULL) nearby_people.push_back(person);
        }
    }
    auto central_person_iterator = std::find(nearby_people.begin(), nearby_people.end(), board.get_person(y, x));
    nearby_people.remove(central_person_iterator);
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

void evolve(Board& board)
{
    
}