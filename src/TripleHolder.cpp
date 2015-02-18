#include "TripleHolder.hpp"
#include "Cell.hpp"
#include "ValueEliminator.hpp"

TripleHolder::TripleHolder(Cell &cell1, Cell &cell2,Cell &cell3):
        first(cell1),
        second(cell2),
        third(cell3){}

Cell &TripleHolder::getFirst(){return first;}
Cell &TripleHolder::getSecond(){return second;}
Cell &TripleHolder::getThird(){return third;}
Cell &TripleHolder::getCell(int const cell_index) const{
        switch(cell_index){
        case 0: return first;
        case 1: return second;
        case 2: return third;
        }
}


void TripleHolder::flagValues(ValueEliminator &ve) const{
        ve.flag(first);
        ve.flag(second);
        ve.flag(third);
}

bool TripleHolder::isValuePresent(unsigned char iValue) const{
        bool isPresent = false;
        isPresent |= (first == iValue);
        isPresent |= (second == iValue);
        isPresent |= (third == iValue);
        return isPresent;
}

bool TripleHolder::isFull() const {
        unsigned char noElement = '0';
        return !(first == noElement) || !(second == noElement) || !(third == noElement);
}

TripleHolder & TripleHolder::operator=(TripleHolder rh) {
        first = rh.getFirst();
        second = rh.getSecond();
        third = rh.getThird();
}
