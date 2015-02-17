#ifndef ROWHOLDER_HPP
#define ROWHOLDER_HPP

#include "Cell.hpp"
#include "TripleHolder.hpp"

class RowHolder : public TripleHolder{
public:
        RowHolder(Cell &g, Cell &c, Cell &d): TripleHolder(g,c,d){};

        Cell &G();
        Cell &C();
        Cell &D();
};


#endif
