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
        text[i * 4 + j].setFillColor(sf::Color::White);
        if (game.Get(i, j) == 2)
        {
          square[i * 4 + j].setFillColor(sf::Color(235, 228, 220));
          text[i * 4 + j].setFillColor(sf::Color(116, 110, 102));
        }
        if (game.Get(i, j) == 4)
        {
          square[i * 4 + j].setFillColor(sf::Color(234, 225, 205));
          text[i * 4 + j].setFillColor(sf::Color(116, 110, 102));
        }
        if (game.Get(i, j) == 8)
        {
          square[i * 4 + j].setFillColor(sf::Color(226, 181, 129));
        }
        if (game.Get(i, j) == 16)
        {
          square[i * 4 + j].setFillColor(sf::Color(223, 155, 107));
        }
        if (game.Get(i, j) == 32)
        {
          square[i * 4 + j].setFillColor(sf::Color(219, 131, 100));
        }
        if (game.Get(i, j) == 64)
        {
          square[i * 4 + j].setFillColor(sf::Color(217, 106, 69));
        }
        if (game.Get(i, j) == 128)
        {
          square[i * 4 + j].setFillColor(sf::Color(227, 209, 126));
        }
        if (game.Get(i, j) == 256)
        {
          square[i * 4 + j].setFillColor(sf::Color(227, 206, 113));
        }
        if (game.Get(i, j) == 512)
        {
          square[i * 4 + j].setFillColor(sf::Color(227, 203, 100));
        }
        if (game.Get(i, j) == 1024)
        {
          square[i * 4 + j].setFillColor(sf::Color(225, 199, 87));
        }
        if (game.Get(i, j) == 2048)
        {
          square[i * 4 + j].setFillColor(sf::Color(224, 195, 77));
        }
        if (game.Get(i, j) > 2048)
        {
          square[i * 4 + j].setFillColor(sf::Color::Black);
        }
        square[i * 4 + j].setSize({100.f, 100.f});
        // square[i * 4 + j].setFillColor(sf::Color(188, 231, 84)); // Light blue
        square[i * 4 + j].setOutlineColor(sf::Color::Black);
        square[i * 4 + j].setOutlineThickness(3.f);
        square[i * 4 + j].setPosition({i * 100.f + 3.f * i + 3.f, j * 100.f + 3.f * j + 3.f}); // Position of top-left corner

        text[i * 4 + j].setString(std::to_string(game.Get(i, j)));
        if (game.Get(i, j) > 512)
        {
          text[i * 4 + j].setCharacterSize(40);
        }
        else if (game.Get(i, j) > 64)
        {
          text[i * 4 + j].setCharacterSize(50);
        }
        else
        {
          text[i * 4 + j].setCharacterSize(80);
        }
        // text[i * 4 + j].setFillColor(sf::Color::Black);
        text[i * 4 + j].setStyle(sf::Text::Style::Bold);

        // Center the text inside the square
        sf::FloatRect textBounds = text[i * 4 + j].getLocalBounds();
        auto textSize = textBounds.size;
        textSize.x /= 2.0f;
        textSize.y /= 1.1f;
        text[i * 4 + j].setPosition(square[i * 4 + j].getPosition() +
                                    square[i * 4 + j].getGeometricCenter() - textSize);
      }
      else
      {
        square[i * 4 + j].setFillColor(sf::Color::White);
        square[i * 4 + j].setOutlineColor(sf::Color::Black);
        square[i * 4 + j].setOutlineThickness(3.f);
        square[i * 4 + j].setPosition({i * 100.f + 3.f * i + 3.f, j * 100.f + 3.f * j + 3.f});
      }
    }
  }
}

int main()
{
  Game2048 game;
  // Create the window with SFML 3.1's new VideoMode syntax
  sf::RenderWindow window(sf::VideoMode({415, 442}), "Game 2048");
  window.setFramerateLimit(60);

  sf::Font font;
  // Note: Replace "arial.ttf" with a path to a real font file on your system.
  if (!font.openFromFile("ArialRegular.ttf"))
  {
    std::cerr << "Error loading font 'arial.ttf'. Make sure the file exists in the working directory.\n";
    return -1;
  }

  sf::Text score(font, (L"Очки: " + std::to_wstring(game.getScore())), 24);
  score.setPosition({15.0f, 415.0f});
  score.setFillColor(sf::Color::Blue);
  score.setStyle(sf::Text::Bold);

  std::vector<sf::RectangleShape>
      square(16);
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
        else if (game.getStateGame())
        {
          game.initGame();
          print(game, square, text);
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::A || keyPressed->scancode == sf::Keyboard::Scancode::Left)
        {
          game.move_left();
          print(game, square, text);
          score.setString(L"Очки: " + std::to_wstring(game.getScore()));
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::D || keyPressed->scancode == sf::Keyboard::Scancode::Right)
        {
          game.move_right();
          print(game, square, text);
          score.setString(L"Очки: " + std::to_wstring(game.getScore()));
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::W || keyPressed->scancode == sf::Keyboard::Scancode::Up)
        {
          game.move_up();
          print(game, square, text);
          score.setString(L"Очки: " + std::to_wstring(game.getScore()));
        }
        else if (keyPressed->scancode == sf::Keyboard::Scancode::S || keyPressed->scancode == sf::Keyboard::Scancode::Down)
        {
          game.move_down();
          print(game, square, text);
          score.setString(L"Очки: " + std::to_wstring(game.getScore()));
        }
      }
    }

    sf::Text endGame(font, L"Конец игры!", 70);
    endGame.setPosition({10.0f, 200.0f});
    endGame.setFillColor(sf::Color::Red);
    endGame.setStyle(sf::Text::Bold);

    window.clear(sf::Color::White);
    window.draw(score);
    for (size_t i = 0; i < SIZE; ++i)
    {
      for (size_t j = 0; j < SIZE; ++j)
      {
        window.draw(square[i * 4 + j]);
        if (game.Get(i, j) > 0)
        {
          window.draw(text[i * 4 + j]);
        }
      }
    }
    if (game.getStateGame())
    {
      window.draw(endGame);
    }
    window.display();
  }
}
