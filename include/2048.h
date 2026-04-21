#pragma once

class Game2048
{
private:
  int board[4][4] = {{0}, {0}, {0}, {0, 0, 0, 2}};
  int score = 0;
};