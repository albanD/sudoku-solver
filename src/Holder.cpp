#include "Holder.hpp"
#include "Cell.hpp"

TripleHolder::TripleHolder(){};

TripleHolder::TripleHolder(Cell* cell1, Cell* cell2, Cell* cell3){
        first = cell1;
        second = cell2;
        third = cell3;
}

Cell* TripleHolder::getFirst(){return first;}
Cell* TripleHolder::getSecond(){return second;}
Cell* TripleHolder::getThird(){return third;}
