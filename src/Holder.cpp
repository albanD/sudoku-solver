#include "Holder.hpp"
#include "Cell.hpp"
#include "Region.hpp"

TripleHolder::TripleHolder(){};

TripleHolder::TripleHolder(Cell* cell1, Cell* cell2, Cell* cell3){
        first = cell1;
        second = cell2;
        third = cell3;
}

Cell* TripleHolder::getFirst(){return first;}
Cell* TripleHolder::getSecond(){return second;}
Cell* TripleHolder::getThird(){return third;}

RowHolder::RowHolder(Cell* g, Cell* c, Cell* d){
        first = g;
        second = c;
        third = d;
}

Cell* RowHolder::G(){return getFirst();}
Cell* RowHolder::C(){return getSecond();}
Cell* RowHolder::D(){return getThird();}


ColumnHolder::ColumnHolder(Cell* t, Cell* c, Cell* b){
        first = t;
        second = c;
        third = b;
}

Cell* ColumnHolder::T(){return getFirst();}
Cell* ColumnHolder::C(){return getSecond();}
Cell* ColumnHolder::B(){return getThird();}

RegionHolder::RegionHolder(Region region){
        NO = &(region.NO);
        N = &(region.N);
        NE = &(region.NE);
        O = &(region.O);
        C = &(region.C);
        E = &(region.E);
        SO = &(region.SO);
        S = &(region.S);
        SE = &(region.SE);
}

Cell* RegionHolder::getNO(){return NO;}
Cell* RegionHolder::getN(){return N;}
Cell* RegionHolder::getNE(){return NE;}
Cell* RegionHolder::getO(){return O;}
Cell* RegionHolder::getC(){return C;}
Cell* RegionHolder::getE(){return E;}
Cell* RegionHolder::getSO(){return SO;}
Cell* RegionHolder::getS(){return S;}
Cell* RegionHolder::getSE(){return SE;}
