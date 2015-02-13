#include "Holder.hpp"
#include "Cell.hpp"
#include "Region.hpp"

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


void TripleHolder::flagValues(ValueEliminator ve) const{
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


Cell* const RowHolder::G(){return getFirst();}
Cell* const RowHolder::C(){return getSecond();}
Cell* const RowHolder::D(){return getThird();}

Cell* const ColumnHolder::T(){return getFirst();}
Cell* const ColumnHolder::C(){return getSecond();}
Cell* const ColumnHolder::B(){return getThird();}

RegionHolder::RegionHolder(Region &region):
        NO(&(region.NO)),
        N(&(region.N)),
        NE(&(region.NE)),
        O(&(region.O)),
        C(&(region.C)),
        E(&(region.E)),
        SO(&(region.SO)),
        S(&(region.S)),
        SE(&(region.SE)){}

Cell* const RegionHolder::getNO() const {return NO;}
Cell* const RegionHolder::getN() const {return N;}
Cell* const RegionHolder::getNE() const {return NE;}
Cell* const RegionHolder::getO() const {return O;}
Cell* const RegionHolder::getC() const {return C;}
Cell* const RegionHolder::getE() const {return E;}
Cell* const RegionHolder::getSO() const {return SO;}
Cell* const RegionHolder::getS() const {return S;}
Cell* const RegionHolder::getSE() const {return SE;}

Cell* const RegionHolder::getCell(int const cell_index) const{
        switch(cell_index){
        case 0: return NO;
        case 1: return N;
        case 2: return NE;
        case 3: return O;
        case 4: return C;
        case 5: return E;
        case 6: return SO;
        case 7: return S;
        case 8: return SE;
        }
}


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


void RegionHolder::flagValues(ValueEliminator ve) const{
        ve.flag(*NO);
        ve.flag(*N);
        ve.flag(*NE);
        ve.flag(*O);
        ve.flag(*C);
        ve.flag(*E);
        ve.flag(*SO);
        ve.flag(*S);
        ve.flag(*SE);
}

bool RegionHolder::isValuePresent(unsigned char iValue) const{
        bool isValuePresent = false;
        isValuePresent|= (*NO == iValue);
        isValuePresent|= (*N == iValue);
        isValuePresent|= (*NE == iValue);
        isValuePresent|= (*O == iValue);
        isValuePresent|= (*C == iValue);
        isValuePresent|= (*E == iValue);
        isValuePresent|= (*SO == iValue);
        isValuePresent|= (*S == iValue);
        isValuePresent|= (*SE == iValue);

}
