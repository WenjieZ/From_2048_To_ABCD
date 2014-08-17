#ifndef VECTORBOARD_H
#define VECTORBOARD_H

#include <vector>

class VectorBoard
{
    public:
        VectorBoard();
        VectorBoard& generate(float realRandom1, float realRandom2);
        VectorBoard& move(char direction);
        int getValue(int i, int j);
    private:
        VectorBoard& transpose();
        VectorBoard& lrFlip();
        VectorBoard& reduce();
        std::vector< std::vector<int> > _board;
};

#endif // VECTORBOARD_H
