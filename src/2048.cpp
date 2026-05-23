/****************************************/
/*Autor: Nikolay Martynovich(nike@bk.ru)*/
/****************************************/

#include <iostream>
#include <string>
#include "include/2048.h"
#include <SFML/Graphics.hpp>
#include <vector>

void print(Game2048 &game, std::vector<sf::RectangleShape> &square, std::vector<sf::Text> &text)
{
  for (size_t i = 0; i < SIZE; ++i)
  {
    for (size_t j = 0; j < SIZE; ++j)
    {
      if (game.Get(i, j) > 0)
      {
        // --- Square shape (SFML 3.1 style) ---
        // Create a rectangle with a given size
        square[(i + 1) * (j + 1) - 1].setSize({100.f, 100.f});
        square[(i + 1) * (j + 1) - 1].setFillColor(sf::Color(100, 150, 250)); // Light blue
        square[(i + 1) * (j + 1) - 1].setOutlineColor(sf::Color::Black);
        square[(i + 1) * (j + 1) - 1].setOutlineThickness(3.f);
        square[(i + 1) * (j + 1) - 1].setPosition({i * 100.f + 3.f, j * 100.f + 3.f}); // Position of top-left corner

        // --- Text (inscription) ---

        // Create a text object (SFML 3.1 style)
        // text[(i + 1) * (j + 1) - 1].setFont(font);
        text[(i + 1) * (j + 1) - 1].setString(std::to_string(game.Get(i, j)));
        text[(i + 1) * (j + 1) - 1].setCharacterSize(80);
        text[(i + 1) * (j + 1) - 1].setFillColor(sf::Color::Black);
        text[(i + 1) * (j + 1) - 1].setStyle(sf::Text::Style::Bold);

        // Center the text inside the square
        sf::FloatRect textBounds = text[(i + 1) * (j + 1) - 1].getLocalBounds();
        auto textSize = textBounds.size;
        textSize.x /= 2.0f;
        textSize.y /= 1.1f;
        text[(i + 1) * (j + 1) - 1].setPosition(square[(i + 1) * (j + 1) - 1].getPosition() +
                                                square[(i + 1) * (j + 1) - 1].getGeometricCenter() - textSize);
      }
      else
      {
        square[(i + 1) * (j + 1) - 1].setSize({100.f, 100.f});
        square[(i + 1) * (j + 1) - 1].setFillColor(sf::Color::White); // Light blue
        square[(i + 1) * (j + 1) - 1].setOutlineColor(sf::Color::Black);
        square[(i + 1) * (j + 1) - 1].setOutlineThickness(3.f);
        square[(i + 1) * (j + 1) - 1].setPosition({i * 100.f + 3.f, j * 100.f + 3.f}); // Position of top-left corner
      }
    }
  }
}

int main()
{
  Game2048 game;
  // Create the window with SFML 3.1's new VideoMode syntax
  sf::RenderWindow window(sf::VideoMode({406, 406}), "Game 2048");
  window.setFramerateLimit(60);

  sf::Font font;
  // Note: Replace "arial.ttf" with a path to a real font file on your system.
  if (!font.openFromFile("ArialRegular.ttf"))
  {
    std::cerr << "Error loading font 'arial.ttf'. Make sure the file exists in the working directory.\n";
    return -1;
  }

  std::vector<sf::RectangleShape> square(16);
  std::vector<sf::Text> text;
  text.reserve(16); // резервируем память для 16 элементов
  for (int i = 0; i < 16; ++i)
  {
    // emplace_back передаёт аргументы в конструктор sf::Text
    text.emplace_back(font, "0", 80); // шрифт, строка, размер
  }

  print(game, square, text);

  while (window.isOpen())
  {
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>())
        window.close();
      else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
      {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
          window.close();
        else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
        {
          game.move_left();
          print(game, square, text);
        }
      }
    }

    window.clear(sf::Color::White);
    for (size_t i = 0; i < SIZE; ++i)
    {
      for (size_t j = 0; j < SIZE; ++j)
      {
        if (game.Get(i, j) > 0)
        {
          window.draw(square[(i + 1) * (j + 1) - 1]);
          window.draw(text[(i + 1) * (j + 1) - 1]);
        }
      }
    }
    window.display();
  }
}
/*int main()
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
}*/