#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <cmath>
#include "game.h"

void Game::run()
{
    _window.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT),"From 2048 To ABCD");
    _window.setFramerateLimit(10);
    std::time_t rd = std::abs(std::time(NULL));
    std::default_random_engine gen(rd);
    std::uniform_real_distribution<> dis(0, 1);
    _board.generate(dis(gen),dis(gen)).generate(dis(gen),dis(gen));
    sf::Font font;
    font.loadFromFile("res/calibri.ttf");

    while (_window.isOpen())
    {
        char input = ' ';
        processEvents(input);
        update(input, dis(gen), dis(gen));
        render(font);
    }
}

void Game::processEvents(char& direction)
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                direction = 'N';
                break;
            case sf::Keyboard::Down:
                direction = 'S';
                break;
            case sf::Keyboard::Left:
                direction = 'W';
                break;
            case sf::Keyboard::Right:
                direction = 'E';
                break;
            default:
                break;
            }
        default:
            break;
        }
    }
}

void Game::update(char& direction, float realRandom1, float realRandom2)
{
    if (direction != ' ') _board.move(direction).generate(realRandom1,realRandom2);
    direction = ' ';
}

void Game::render(const sf::Font& font)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(CELL_SIZE);
    text.setColor(sf::Color::White);

    _window.clear();
    for (int i = 0; i < ROW_NUM; ++i)
        for (int j = 0; j < COL_NUM; ++j)
            if (_board.getValue(i,j) != -1)
            {
                text.setString(S[_board.getValue(i,j)]);
                text.setPosition(j * CELL_SIZE, i * CELL_SIZE);
                _window.draw(text);
            }
    _window.display();
}

sf::RenderWindow Game::_window;
VectorBoard Game::_board;
const std::string Game::S = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

