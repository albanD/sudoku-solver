#include "TripleHolder.hpp"

TripleHolder::TripleHolder(Cell* const cell1, Cell* const cell2,Cell* const cell3):
        first(cell1),
        second(cell2),
        third(cell3){}

Cell* const TripleHolder::getFirst(){return first;}
Cell* const TripleHolder::getSecond(){return second;}
Cell* const TripleHolder::getThird(){return third;}
Cell* const TripleHolder::getCell(int const cell_index) const{
        switch(cell_index){
        case 0: return first;
        case 1: return second;
        case 2: return third;
        }
}


void TripleHolder::flagValues(ValueEliminator &ve) const{
        ve.flag(*first);
        ve.flag(*second);
        ve.flag(*third);
}

bool TripleHolder::isValuePresent(unsigned char iValue) const{
        bool isPresent = false;
        isPresent |= (*first == iValue);
        isPresent |= (*second == iValue);
        isPresent |= (*third == iValue);
        return isPresent;
}
