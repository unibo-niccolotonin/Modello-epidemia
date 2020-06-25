#pragma once
#include <cassert>
#include <iostream>
#include <vector>

enum state { SUSCEPTIBLE, DEAD, IMMUNE, NON_EXISTANT, INFECTED };
class Cell {
public:
  int vx, vy;
  int clock;
  state status;
  Cell(state stato) : vx(0), vy(0), clock(0), status(stato){};
};

class Board {
  int size_;
  std::vector<Cell> board_;
  static Cell null_cell_;

public:
    static int infection_radius;
    static float infection_probability;
    static int infection_time;
    static float mortality_rate;

  float cell_length;
  float graph_height;
  float graph_column_width;

  int get_size() const { return size_; }
  bool insertCell(int r, int c);
  bool insertCell(int r, int c, state cell_state);

  Cell &operator()(int y, int x);

  Cell operator()(int y, int x) const;

  Board(int n)
      : size_(n), board_(n * n, Cell(NON_EXISTANT)),
        cell_length(5.0f), graph_height(100.0f), graph_column_width(2.0f){};
};
