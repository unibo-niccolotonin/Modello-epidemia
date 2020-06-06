#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "board.hpp"
#include "board_functions.hpp"

void draw (sf::RenderWindow& window, Board const& board, float const& length)
{
    float x = 0.f;
    float y = 0.f;
    sf::RectangleShape rect(sf::Vector2f(length, length));
    rect.setPosition(sf::Vector2f(x, y));

    for (int i = 0; i < board.get_size(); i++)
    {
        for (int j = 0; j < board.get_size(); j++)
        {
            switch(board(i, j).status)
            {
                case state::non_existant:
                    rect.setFillColor(sf::Color(30,30,30,255)); //Black
                    break;
                case state::susceptible:
                    rect.setFillColor(sf::Color(54, 42, 201, 255)); //Blue
                    break;
                case state::infected:
                    rect.setFillColor(sf::Color(209, 26, 29, 255)); //Red
                    break;
                case state::immune:
                    rect.setFillColor(sf::Color(43, 229, 6, 255)); //Green
                    break;
                case state::dead:
                    rect.setFillColor(sf::Color(111, 111, 111, 255)); //Gray
                    break;
            }
            rect.setPosition(sf::Vector2f(x, y));
            window.draw(rect);

            x += length;
        }
        y += length;
        x = 0.f;
    }
}
