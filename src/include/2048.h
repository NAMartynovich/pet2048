#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

constexpr int SIZE = 4;

class Game2048
{
private:
  const int arr[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 4};
  std::vector<int> board[SIZE] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
  int score = 0;
  bool endGame = false;

  void random_space(int &i, int &j)
  {
    i = std::rand() % 4;
    j = std::rand() % 4;
  }

  void add_rand_num()
  {
    int count = 0;
    for (size_t i = 0; i != SIZE; ++i)
    {
      for (size_t j = 0; j != SIZE; ++j)
      {
        if (board[i][j] == 0)
        {
          ++count;
        }
      }
    }
    if (count == 0)
    {
      endGame = true;
    }
    if (count == 1)
    {
      for (size_t i = 0; i != SIZE; ++i)
      {
        for (size_t j = 0; j != SIZE; ++j)
        {
          if (board[i][j] == 0)
          {
            board[i][j] = arr[std::rand() % 10];
          }
        }
      }
    }
    else
    {
      count = std::rand() % count;
      for (size_t i = 0; i != SIZE; ++i)
      {
        for (size_t j = 0; j != SIZE; ++j)
        {
          if (board[i][j] == 0)
          {
            --count;
          }
          if (count == 0)
          {
            if (board[i][j] == 0)
              board[i][j] = arr[std::rand() % 10];
            break;
          }
        }
        if (count == 0)
          break;
      }
    }
  }

  void reverse()
  {
    for (size_t i = 0; i < SIZE; ++i)
    {
      std::swap(board[i][0], board[i][SIZE - 1]);
      std::swap(board[i][1], board[i][SIZE - 2]);
    }
  }

  void transparent()
  {
    std::swap(board[0][1], board[1][0]);
    std::swap(board[0][2], board[2][0]);
    std::swap(board[0][3], board[3][0]);
    std::swap(board[1][2], board[2][1]);
    std::swap(board[1][3], board[3][1]);
    std::swap(board[2][3], board[3][2]);
  }

  void transparent2()
  {
    std::swap(board[0][0], board[3][3]);
    std::swap(board[0][1], board[2][3]);
    std::swap(board[0][2], board[1][3]);
    std::swap(board[1][0], board[3][2]);
    std::swap(board[1][1], board[2][2]);
    std::swap(board[2][0], board[3][1]);
  }

public:
  Game2048()
  {
    int i, j;
    std::srand(std::time(nullptr));
    random_space(i, j);
    board[i][j] = 2;
    random_space(i, j);
    board[i][j] = 4;
  }
  // Определить случайное пустое место

  void move_left()
  {
    for (size_t i = 0; i < SIZE; ++i)
    {
      auto j = board[i].begin();
      while (j != board[i].end())
      {
        if (*j == 0)
        {
          board[i].erase(j);
        }
        else
        {
          ++j;
        }
      }
      if (board[i].size() > 1)
      {
        j = board[i].begin();
        while (j != board[i].end() - 1)
        {
          if (*j > 0 && *j == *(j + 1))
          {
            *j += *(j + 1);
            score += *j;
            board[i].erase(j + 1);
          }
          else
          {
            ++j;
          }
        }
      }
      while (board[i].size() < 4)
      {
        board[i].push_back(0);
      }
    }
    add_rand_num();
  }

  void move_right()
  {
    reverse();
    move_left();
    reverse();
  }

  void move_up()
  {
    transparent();
    move_left();
    transparent();
  }

  void move_down()
  {
    transparent2();
    move_left();
    transparent2();
  }

  const int Get(int i, int j) const
  {
    return board[j][i];
  }

  const int getScore() const
  {
    return score;
  }

  const bool getStateGame() const
  {
    return !endGame;
  }

  friend std::ostream &operator<<(std::ostream &os, const Game2048 &game)
  {
    for (size_t i = 0; i < SIZE; ++i)
    {
      for (size_t j = 0; j < SIZE; ++j)
      {
        os << game.board[i][j] << " ";
      }
      os << std::endl;
    }
    os << "Score: " << game.score << std::endl;
    return os;
  }
};