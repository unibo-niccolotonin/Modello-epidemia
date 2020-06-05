#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include "board.hpp"
#include "rules.hpp"

int main(int argc, const char * argv[]) {
    Board board(20);
    
    float const length = 10.f;
    
    board.insertCell(1, 1, state::infected);
    
    
    
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulazione infezione", sf::Style::Default);
    window.setFramerateLimit(60);

    sf::Event event;
    while(window.isOpen())
    {
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = std::floor(event.mouseButton.x / length);
                int y = std::floor(event.mouseButton.y / length);
                
                // Occorre risolvere il problema che non è calibrato quando la finestra viene ridimensionata
                
                board.insertCell(y, x);
            }
        }
    //Aggiunge una cellula

    window.clear();

    //Update
    board = evolve(board);
    
    float x = 0.f;
    float y = 0.f;
    sf::RectangleShape rect(sf::Vector2f(length, length));
    rect.setPosition(sf::Vector2f(x, y));

    //Draw board
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

    //Display board
    window.display();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(00));
    }
    return 0;
    
}
