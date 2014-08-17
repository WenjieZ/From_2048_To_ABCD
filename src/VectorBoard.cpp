#include <random>
#include <cmath>
#include <vector>
#include "Game.h"
#include "VectorBoard.h"

VectorBoard::VectorBoard()
{
    std::vector<int> temp(Game::COL_NUM, -1);
    for (int i = 0; i < Game::ROW_NUM; ++i)
        _board.push_back(temp);
}

VectorBoard& VectorBoard::generate(float realRandom1, float realRandom2)
{
    int numEmptyCells = 0;
    for (int i = 0; i < Game::ROW_NUM; ++i)
        for (int j = 0; j < Game::COL_NUM; ++j)
            if (_board[i][j] == -1) ++numEmptyCells;

    int position = std::ceil(realRandom1 * numEmptyCells);
    for (int i = 0; i < Game::ROW_NUM; ++i)
        for (int j = 0; j < Game::COL_NUM; ++j)
        {
            if (_board[i][j] == -1) --position;
            if (position == 0)
            {
                int power = std::ceil(- std::log2(realRandom2));
                if (power > 11) power = 11;
                _board[i][j] = power - 1;
                position = -1;
            }
        }
    return *this;
}

VectorBoard& VectorBoard::move(char direction)
{
    switch (direction)
    {
    case 'W':
        reduce();
        break;
    case 'N':
        transpose().reduce().transpose();
        break;
    case 'E':
        lrFlip().reduce().lrFlip();
        break;
    case 'S':
        transpose().lrFlip().reduce().lrFlip().transpose();
        break;
    }
    return *this;
}

int VectorBoard::getValue(int i, int j)
{
    return _board[i][j];
}

VectorBoard& VectorBoard::reduce()
{
    for (int i = 0; i < Game::ROW_NUM; ++i)
        for (int j = 0, k = 0; j < Game::COL_NUM; ++j)
        {
            while (k < Game::COL_NUM && _board[i][k] == -1) ++k;
            if (k == Game::COL_NUM) break;
            int l = k + 1;
            while (l < Game::COL_NUM && _board[i][l] == -1) ++l;
            if (l < Game::COL_NUM && _board[i][k] == _board[i][l])
            {
                int temp = _board[i][k] + 1;
                _board[i][k] = _board[i][l] = -1;
                _board[i][j] = temp;
                k = l + 1;
            } else {
                int temp = _board[i][k];
                _board[i][k] = -1;
                _board[i][j] = temp;
                k = l;
            }
        }
    return *this;
}

VectorBoard& VectorBoard::transpose()
{
    for (int i = 0; i < Game::ROW_NUM; ++i)
        for (int j = i+1; j < Game::COL_NUM; ++j)
        {
            char temp = _board[i][j];
            _board[i][j] = _board[j][i];
            _board[j][i] = temp;
        }
    return *this;
}

VectorBoard& VectorBoard::lrFlip()
{
    for (int i = 0; i < Game::ROW_NUM; ++i)
        for (int j = 0; j < Game::COL_NUM / 2; ++j)
        {
            char temp = _board[i][j];
            _board[i][j] = _board[i][Game::COL_NUM-1-j];
            _board[i][Game::COL_NUM-1-j] = temp;
        }
    return *this;
}
