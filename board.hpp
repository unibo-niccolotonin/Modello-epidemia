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
  int size;
  std::vector<std::vector<Cell>> board_;
  static Cell m_null_cell;

public:
  float cell_length;
  float graph_height;
  float graph_column_width;

  int get_size() const { return size; }
  bool insertCell(int r, int c);
  bool insertCell(int r, int c, state statocellula);

  Cell &operator()(int y, int x);

  Cell operator()(int y, int x) const;

  Board(int n)
      : size(n), board_(n, std::vector<Cell>(n, Cell(NON_EXISTANT))),
        cell_length(5.0f), graph_height(100.0f), graph_column_width(2.0f){};
};
