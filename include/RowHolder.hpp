#ifndef ROWHOLDER_HPP
#define ROWHOLDER_HPP

#include "Cell.hpp"
#include "TripleHolder.hpp"

class RowHolder : public TripleHolder{
public:
        RowHolder(): TripleHolder(){};
        RowHolder(Cell* const g, Cell* const c, Cell* const d): TripleHolder(g,c,d){};

        Cell* const G();
        Cell* const C();
        Cell* const D();
};


#endif
