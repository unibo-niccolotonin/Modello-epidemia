#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <array>
#include <vector>
#include <chrono>
#include <thread>
#include <cmath>
#include "board.hpp"
#include "board_functions.hpp"

int main() {
    Board board(50);
    std::cout << "Suscettibili   Infetti   Rimossi\n";
    //Contiene le varie altezze delle colonne per disegnare il grafico della curva d'infezione
    std::vector<std::array<int, 4> > graph;

    float const length = 10.f;

    board.insertCell(2, 4, INFECTED);
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            board.insertCell(i, j);

    board.cell_length = 10.0f;
    board.graph_column_width = 4.0f;
    board.graph_height = 300.0f;

    sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulazione infezione", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
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
        draw(window, board, graph);

        //Display board
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return 0;

}
