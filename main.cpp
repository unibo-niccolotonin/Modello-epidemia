#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include "board.hpp"
#include "board_functions.hpp"

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
            if (event.type == sf::Event::MouseButtonPressed) //aggiunge una cellula quando si clicca la finestra
            {
                int x = std::floor(event.mouseButton.x / length);
                int y = std::floor(event.mouseButton.y / length);
                
                // Occorre risolvere il problema che non è calibrato quando la finestra viene ridimensionata
                
                board.insertCell(y, x);
            }
        }

    window.clear();

    //Update
    board = evolve(board);

    //Draw board
    draw(window, board, length);

    //Display board
    window.display();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(00));
    }
    return 0;
    
}
