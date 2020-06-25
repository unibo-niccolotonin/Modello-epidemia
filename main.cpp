#include "board.hpp"
#include "evolve.hpp"
#include "draw.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

template<typename T>
void loop_of_failure(T& var, int max_value)
{
    while (std::cin.fail() || var < 0 || var > max_value)
    { //verifica che il valore inserito non sia una stringa e che non sia negativo
        std::cout << "input non valido, inserire un valore corretto: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> var;
    }
}

void set_infection_values(Board const& board)
{
         //questa funzione serve ad inserire le variabili dell'infezione
        std::cout << "inserimento costanti:\n";
        std::cout << "inserire il raggio di infezione: ";
        std::cin >> Board::infection_radius;
        
        loop_of_failure(Board::infection_radius, board.get_size());

        std::cout << "\ninserire la probabilità di infezione: ";
        std::cin >> Board::infection_probability;
        
        loop_of_failure(Board::infection_probability, 1);

        std::cout << "\ninserire il tempo di durata dell'infezione: ";
        std::cin >> Board::infection_time;
        
        loop_of_failure(Board::infection_time, 1000000);

        std::cout << "\ninserire la probabilità di morte di una cellula infetta: ";
        std::cin >> Board::mortality_rate;
        
        loop_of_failure(Board::mortality_rate, 1);
}

int main() {

  Board board(50);

  set_infection_values(board);

  board.fill_board(100);

  std::cout << "Suscettibili   Infetti   Rimossi\n";
    
  // Contiene le varie altezze delle colonne per disegnare il grafico della
  // curva d'infezione
  std::vector<std::array<int, 4> > graph_columns_heights;

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
