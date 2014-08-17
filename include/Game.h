#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>
#include "VectorBoard.h"

class Game
{
public:
    static void run();
    const static int ROW_NUM = 4;
    const static int COL_NUM = 4;
    const static int CELL_SIZE = 100;
    const static int SCREEN_WIDTH  = COL_NUM * CELL_SIZE;
    const static int SCREEN_HEIGHT = ROW_NUM * CELL_SIZE;
    const static std::string S;
private:
    static void processEvents(char& direction);
    static void update(char& direction, float realRandom1, float realRandom2);
    static void render(const sf::Font& font);
    static sf::RenderWindow _window;
    static VectorBoard _board;
};


#endif // GAME_H_INCLUDED
