#ifndef TRIPLEHOLDER_HPP
#define TRIPLEHOLDER_HPP

#include "Cell.hpp"
#include "ValueEliminator.hpp"

class TripleHolder{
public:
        TripleHolder(Cell* const cell1, Cell* const cell2, Cell* const cell3);

        Cell* const getFirst();
        Cell* const getSecond();
        Cell* const getThird();
        Cell* const getCell(int const cell_index) const;

        void flagValues(ValueEliminator &ve) const;
        bool isValuePresent(unsigned char iValue) const;

protected:
        Cell* const first;
        Cell* const second;
        Cell* const third;
};


#endif