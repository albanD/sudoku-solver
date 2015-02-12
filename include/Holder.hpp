#ifndef HOLDER_HPP
#define HOLDER_HPP

#include "Cell.hpp"
#include "Region.hpp"

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

class ColumnHolder : protected TripleHolder{
public:
        ColumnHolder(Cell* t, Cell* c, Cell* b);

        Cell* T();
        Cell* C();
        Cell* B();
};


class RegionHolder{
public:
        RegionHolder(Region region);
private:
        Cell* NO;
        Cell* N;
        Cell* NE;
        Cell* O;
        Cell* C;
        Cell* E;
        Cell* SO;
        Cell* S;
        Cell* SE;
};

#endif
