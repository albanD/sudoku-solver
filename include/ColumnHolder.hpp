#ifndef COLUMNHOLDER_HPP
#define COLUMNHOLDER_HPP

#include "Cell.hpp"
#include "TripleHolder.hpp"


class ColumnHolder : public TripleHolder{
public:
        ColumnHolder(Cell& t, Cell& c, Cell& b): TripleHolder(t,c,b){};

        Cell &T();
        Cell &C();
        Cell &B();
};


#endif
