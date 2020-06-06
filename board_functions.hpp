#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.hpp"

Board evolve(Board const& board);
void draw(sf::RenderWindow const& window, Board const& board, float const& length);