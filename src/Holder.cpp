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

Cell* RegionHolder::getNO() const {return NO;}
Cell* RegionHolder::getN() const {return N;}
Cell* RegionHolder::getNE() const {return NE;}
Cell* RegionHolder::getO() const {return O;}
Cell* RegionHolder::getC() const {return C;}
Cell* RegionHolder::getE() const {return E;}
Cell* RegionHolder::getSO() const {return SO;}
Cell* RegionHolder::getS() const {return S;}
Cell* RegionHolder::getSE() const {return SE;}


RowHolder RegionHolder::topRow(){return RowHolder(getNO(),getN(),getNE());}
RowHolder RegionHolder::middleRow(){return RowHolder(getO(),getC(),getE());}
RowHolder RegionHolder::bottomRow(){return RowHolder(getSO(),getS(),getSE());}
ColumnHolder RegionHolder::leftColumn(){return ColumnHolder(getNO(),getO(),getSO());}
ColumnHolder RegionHolder::middleColumn(){return ColumnHolder(getN(),getC(),getS());}
ColumnHolder RegionHolder::rightColumn(){return ColumnHolder(getNE(),getE(),getSE());}

const RowHolder RegionHolder::topRow() const{return RowHolder(getNO(),getN(),getNE());}
const RowHolder RegionHolder::middleRow() const{return RowHolder(getO(), getC(),getE());}
const RowHolder RegionHolder::bottomRow() const{return RowHolder(getSO(),getS(),getSE());}
const ColumnHolder RegionHolder::leftColumn() const{return ColumnHolder(getNO(), getO(),getSO());}
const ColumnHolder RegionHolder::middleColumn() const{return ColumnHolder(getN(),getC(),getS());}
const ColumnHolder RegionHolder::rightColumn() const{return ColumnHolder(getNE(),getE(),getSE());}
