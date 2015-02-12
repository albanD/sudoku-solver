#ifndef HOLDER_HPP
#define HOLDER_HPP

#include "Cell.hpp"

class TripleHolder{
public:
        TripleHolder();
        TripleHolder(Cell* cell1, Cell* cell2, Cell* cell3);

        Cell* getFirst();
        Cell* getSecond();
        Cell* getThird();

protected:
        Cell* first;
        Cell* second;
        Cell* third;
};

class RowHolder : protected TripleHolder{
public:
        RowHolder(Cell* g, Cell* c, Cell* d);

        Cell* G();
        Cell* C();
        Cell* D();
};

#endif
