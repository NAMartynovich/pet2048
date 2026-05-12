/****************************************/
/*Autor: Nikolay Martynovich(nike@bk.ru)*/
/****************************************/

#include <iostream>
#include <string>
#include "include/2048.h"

int main()
{
  std::cout << "Game 2048!" << std::endl;
  Game2048 game;
  std::cout << game << std::endl;
  std::cout << "Нажмите w, a, s, d или q для выхода" << std::endl;
  char c;
  while ((c = std::getchar()) != 'q')
  {
    switch (c)
    {
    case 'w':
      game.move_up();
      std::cout << game << std::endl;
      break;
    case 'a':
      game.move_left();
      std::cout << game << std::endl;
      break;
    case 's':
      game.move_down();
      std::cout << game << std::endl;
      break;
    case 'd':
      game.move_right();
      std::cout << game << std::endl;
      break;
    }
  }
  return 0;
}