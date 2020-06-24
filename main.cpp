#include "board.hpp"
#include "board_functions.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

int main() {

  Board board(50);
  std::cout << "Suscettibili   Infetti   Rimossi\n";
    
  // Contiene le varie altezze delle colonne per disegnare il grafico della
  // curva d'infezione
  std::vector<std::array<int, 4> > graph_columns_heights;

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
      if (event.type == sf::Event::MouseButtonPressed) // aggiunge una cellula quando si clicca la finestra
      {
        int x = std::floor(event.mouseButton.x / board.cell_length);
        int y = std::floor(event.mouseButton.y / board.cell_length);

        board.insertCell(y, x);
      }
    }
      
    board = evolve(board);
      
    window.clear();
    draw(window, board, graph_columns_heights);
    window.display();

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
  return 0;
}
