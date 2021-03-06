#pragma once
#include "board.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <vector>

void draw(sf::RenderWindow &window, Board const &board,
          std::vector<std::array<int, 4>> &graph_column_heights);
