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

class RowHolder : public TripleHolder{
public:
        RowHolder(Cell* g, Cell* c, Cell* d);

        Cell* G();
        Cell* C();
        Cell* D();
};

class ColumnHolder : public TripleHolder{
public:
        ColumnHolder(Cell* t, Cell* c, Cell* b);

        Cell* T();
        Cell* C();
        Cell* B();
};


class RegionHolder{
public:
        RegionHolder(Region region);

        Cell* getNO() const;
        Cell* getN() const;
        Cell* getNE() const;
        Cell* getO() const;
        Cell* getC() const;
        Cell* getE() const;
        Cell* getSO() const;
        Cell* getS() const;
        Cell* getSE() const;

        RowHolder topRow();
        RowHolder middleRow();
        RowHolder bottomRow();
        ColumnHolder leftColumn();
        ColumnHolder middleColumn();
        ColumnHolder rightColumn();

        const RowHolder topRow() const;
        const RowHolder middleRow() const;
        const RowHolder bottomRow() const;
        const ColumnHolder leftColumn() const;
        const ColumnHolder middleColumn() const;
        const ColumnHolder rightColumn() const;

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
