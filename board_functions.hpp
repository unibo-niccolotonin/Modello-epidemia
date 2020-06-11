#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.hpp"

Board evolve(Board const& board);
void draw(sf::RenderWindow& window, Board const& board, int const&cycle);
