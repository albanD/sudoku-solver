#ifndef HOLDER_HPP
#define HOLDER_HPP

#include "Cell.hpp"
#include "Region.hpp"
#include "ValueEliminator.hpp"

class TripleHolder{
public:
        TripleHolder(Cell* const cell1, Cell* const cell2, Cell* const cell3);

        Cell* const getFirst();
        Cell* const getSecond();
        Cell* const getThird();
        Cell* const getCell(int const cell_index) const;

        void flagValues(ValueEliminator ve) const;
        bool isValuePresent(unsigned char iValue) const;

protected:
        Cell* const first;
        Cell* const second;
        Cell* const third;
};

class RowHolder : public TripleHolder{
public:
        RowHolder(Cell* const g, Cell* const c, Cell* const d): TripleHolder(g,c,d){};

        Cell* const G();
        Cell* const C();
        Cell* const D();
};

class ColumnHolder : public TripleHolder{
public:
        ColumnHolder(Cell* t, Cell* c, Cell* b): TripleHolder(t,c,b){};

        Cell* const T();
        Cell* const C();
        Cell* const B();
};


class RegionHolder{
public:
        RegionHolder(Region &region);

        Cell* const getNO() const;
        Cell* const getN() const;
        Cell* const getNE() const;
        Cell* const getO() const;
        Cell* const getC() const;
        Cell* const getE() const;
        Cell* const getSO() const;
        Cell* const getS() const;
        Cell* const getSE() const;
        Cell* const getCell(int const cell_index) const;

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

        void flagValues(ValueEliminator ve) const;
        bool isValuePresent(unsigned char iValue) const;
private:
        Cell* const NO;
        Cell* const N;
        Cell* const NE;
        Cell* const O;
        Cell* const C;
        Cell* const E;
        Cell* const SO;
        Cell* const S;
        Cell* const SE;
};

#endif
