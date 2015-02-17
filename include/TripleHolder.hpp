#ifndef TRIPLEHOLDER_HPP
#define TRIPLEHOLDER_HPP

#include "Cell.hpp"
#include "ValueEliminator.hpp"

class TripleHolder{
public:
        TripleHolder(Cell &cell1, Cell &cell2, Cell &cell3);

        Cell &getFirst();
        Cell &getSecond();
        Cell &getThird();
        Cell &getCell(int const cell_index) const;

        void flagValues(ValueEliminator &ve) const;
        bool isValuePresent(unsigned char iValue) const;
        bool isFull() const;
        TripleHolder & operator=(TripleHolder rh);

protected:
        Cell& first;
        Cell& second;
        Cell& third;
};


#endif
