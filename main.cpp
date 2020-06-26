#include "board.hpp"
#include "draw.hpp"
#include "evolve.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>
#include <vector>

void loop_of_failure(float &var, int min_value, int max_value) {
  while (true){
    if (std::cin.fail()){
      std::cout << "input non valido, inserire un valore corretto: ";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cin >> var;
      continue;
    } else if (var < min_value){
      std::cout << "input troppo piccolo, inserire un valore più grande: ";
      std::cin >> var;
      continue;
    } else if (var > max_value){
      std::cout << "input troppo grande, inserire un valore più piccolo: ";
      std::cin >> var;
      continue;
    }
    break;
  }
}

// questa funzione serve ad inserire le variabili dell'infezione
void set_values(Board &board) {
  float float_radius;
  float float_time;
  float n_cells;
  
  std::cout << "inserimento costanti:\n";

  // Assegna un valore a Board::infection_radius
  std::cout << "inserire il raggio di infezione: ";
  std::cin >> float_radius;
  loop_of_failure(float_radius, 0, board.get_size());
  Board::infection_radius = static_cast<int>(float_radius);

  // Assegna un valore a Board::infection_probability
  std::cout << "\ninserire la probabilità di infezione fra 0 e 1: ";
  std::cin >> Board::infection_probability;
  loop_of_failure(Board::infection_probability,0 ,1);

  //Assegna un valore a Board::infection_time
  std::cout << "\ninserire il tempo di durata dell'infezione: ";
  std::cin >> float_time;
  loop_of_failure(float_time, 0, 1000000);
  Board::infection_time = static_cast<int>(float_time);

  //Assegna un valore a Board::mortality_rate
  std::cout << "\ninserire il tasso di mortalità di una cellula infetta fra "
               "0 e 1: ";
  std::cin >> Board::mortality_rate;
  loop_of_failure(Board::mortality_rate,0 ,1);

  //Riempe la griglia con cellule suscettibili
  std::cout << "\ninserire il numero di cellule suscettibili nella griglia, "
               "almeno una e non maggiore a " << (board.get_size() * board.get_size() / 2) << ": ";
  std::cin >> n_cells;
  loop_of_failure(n_cells, 1, board.get_size() * board.get_size() / 2);
  board.fill_board(static_cast<int>(n_cells), SUSCEPTIBLE);

  // Riempe la griglia con cellule infette
  std::cout << "\ninserire il numero di cellule infette nella griglia, non "
               "maggiore a " << (board.get_size()) << ": ";
  std::cin >> n_cells;
  loop_of_failure(n_cells, 0, board.get_size());
  board.fill_board(static_cast<int>(n_cells), INFECTED);
}

int main() {

  Board board(100);

  board.cell_length = 5.0f;
  board.graph_column_width = 2.0f;
  board.graph_height = 300.0f;

  set_values(board);

  std::cout << "Suscettibili   Infetti   Rimossi\n";

  // Contiene le varie altezze delle colonne per disegnare il grafico della
  // curva d'infezione
  std::vector<std::array<int, 4>> graph_columns_heights;

  sf::RenderWindow window(sf::VideoMode(1000, 1000), "Simulazione infezione",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setFramerateLimit(60);

  state mouse_cell_state = SUSCEPTIBLE;

  sf::Event event;
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
      if (event.type ==
          sf::Event::MouseButtonPressed) // aggiunge una cellula quando si
                                         // clicca la finestra
      {
        int x = std::floor(event.mouseButton.x / board.cell_length);
        int y = std::floor(event.mouseButton.y / board.cell_length);

        board.insertCell(y, x, mouse_cell_state);
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::I) {
          mouse_cell_state = INFECTED;
        } else if (event.key.code == sf::Keyboard::S) {
          mouse_cell_state = SUSCEPTIBLE;
        }
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
