#pragma once
#include <iostream>

constexpr int SIZE = 4;

class Game2048
{
private:
  int board[SIZE][SIZE] = {{0}, {0}, {0}, {0, 0, 0, 2}};
  int score = 0;

public:
  friend std::ostream &operator<<(std::ostream &os, Game2048 &game)
  {
    for (size_t i = 0; i < SIZE; ++i)
    {
      for (size_t j = 0; j < SIZE; ++j)
      {
        os << game.board[i][j] << " ";
      }
      os << std::endl;
    }
    return os;
  }
};