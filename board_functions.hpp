#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <array>
#include "board.hpp"

Board evolve(Board const& board);
void draw(sf::RenderWindow& window, Board const& board, std::vector<std::array<int, 4> >& graph);
