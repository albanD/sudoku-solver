#ifndef COLUMNHOLDER_HPP
#define COLUMNHOLDER_HPP

#include "Cell.hpp"
#include "TripleHolder.hpp"


class ColumnHolder : public TripleHolder{
public:
        ColumnHolder(): TripleHolder(){};
        ColumnHolder(Cell* t, Cell* c, Cell* b): TripleHolder(t,c,b){};

        Cell* const T();
        Cell* const C();
        Cell* const B();
};


#endif
