#include "evolve.hpp"
#include "board.hpp"
#include <random>
#include <vector>

namespace random_generation {
static std::random_device rd;
static std::mt19937 device(rd());

static std::uniform_real_distribution<double> distribution_for_probability(0,
                                                                           1);
static std::uniform_int_distribution<int> velocity_distribution(-1, 1);

} // namespace random_generation

void infect_radius(int row, int column, Board const &board, Board &new_board) {
  for (int i = 0; i < (2 * Board::infection_radius + 1); i++) {
    for (int j = 0; j < (2 * Board::infection_radius + 1); j++) {
      int coord_y = (row - Board::infection_radius) + i;
      int coord_x = (column - Board::infection_radius) + j;

      if (new_board(coord_y, coord_x).status == SUSCEPTIBLE) {
        double random = random_generation::distribution_for_probability(
            random_generation::device);

        if (random < Board::infection_probability)
          new_board(coord_y, coord_x).status = INFECTED;
      }
    }
  }
}

void update_infected_cells(int row, int column, Board const &board,
                           Board &new_board) {
  infect_radius(row, column, board, new_board);

  if (new_board(row, column).clock < Board::infection_time) {
    new_board(row, column).clock++;
  } else {
    double nrand = random_generation::distribution_for_probability(
        random_generation::device);
    if (nrand <= Board::mortality_rate) {
      new_board(row, column).status = DEAD;
    } else {
      new_board(row, column).status = IMMUNE;
    }
  }
}

void update_movement(int row, int column, Board const &board,
                     Board &new_board) {
  int failure_counter = 0;

  while (failure_counter !=
         1) // Se si mette un valore maggiore di uno il movimento appare più
            // casuale. La performance del programma però ne risente quando ci
            // sono molte cellule
  {

    new_board(row, column).vx =
        random_generation::velocity_distribution(random_generation::device);
    new_board(row, column).vy =
        random_generation::velocity_distribution(random_generation::device);

    int vx = new_board(row, column).vx;
    int vy = new_board(row, column).vy;

    // Ribalta la velocità della cellula se va fuori la griglia
    if (column + vx >= new_board.get_size() || column + vx < 0)
      vx = -vx;

    if (row + vy >= new_board.get_size() || row + vy < 0)
      vy = -vy;

    if (new_board(row + vy, column + vx).status == NON_EXISTANT) {
      new_board(row + vy, column + vx) = new_board(row, column);
      new_board(row, column) = Cell(NON_EXISTANT);

      break;
    }
    failure_counter++;
  }
}

Board evolve(Board const &board) {
  Board new_board = board;

  for (int row = 0; row < board.get_size(); row++) {
    for (int column = 0; column < board.get_size(); column++) {
      Cell current_cell = board(row, column);

      // Comportamento delle cellule infette
      if (current_cell.status == INFECTED)
        update_infected_cells(row, column, board, new_board);
    }
  }

  /* Abbiamo deciso di mettere il processo di infezione device quello di
   * movimento in for loops separati per diminuire il bias verso le cellule in
   * alto a sinistra che vengono valutate per prima. A dir la verità il bias non
   * si nota se il valore massimo della velocità è basso. In caso contrario
   * però, si può notare che mediamente il numero di cellule mai infettate è più
   * alto. La nostra ipotesi è che questo è causato in quanto esse hanno più
   * probabilità di allontanarsi dal blocco principale di cellule quando vengono
   * inserite inizialmente. Non abbiamo rivelato un consumo della performance
   * significativo aggiungendo i for loops per il movimento, dunque li abbiamo
   * inclusi */

  // Movimento delle cellule

  for (int row = 0; row < board.get_size(); row++) {
    for (int column = 0; column < board.get_size(); column++) {
      Cell current_cell = board(row, column);

      if ((current_cell.status != NON_EXISTANT) &&
          (current_cell.status != DEAD)) {
        update_movement(row, column, board, new_board);
      }
    }
  }

  return new_board;
}
