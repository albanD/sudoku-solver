#include "RegionHolder.hpp"

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


RowHolder RegionHolder::topRow() const {return RowHolder(getNO(),getN(),getNE());}
RowHolder RegionHolder::middleRow() const {return RowHolder(getO(),getC(),getE());}
RowHolder RegionHolder::bottomRow() const {return RowHolder(getSO(),getS(),getSE());}
RowHolder RegionHolder::getRow(int const row_index) const{
        switch(row_index){
        case 0: return topRow();
        case 1: return middleRow();
        case 2: return bottomRow();
        }
}

ColumnHolder RegionHolder::leftColumn() const {return ColumnHolder(getNO(),getO(),getSO());}
ColumnHolder RegionHolder::middleColumn() const {return ColumnHolder(getN(),getC(),getS());}
ColumnHolder RegionHolder::rightColumn() const {return ColumnHolder(getNE(),getE(),getSE());}
ColumnHolder RegionHolder::getColumn(int const col_index) const{
        switch(col_index){
        case 0: return leftColumn();
        case 1: return middleColumn();
        case 2: return rightColumn();
        }
}
void RegionHolder::flagValues(ValueEliminator &ve) const{
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

pair<int,int> RegionHolder::valuePosition(unsigned char iValue) const{

        if(*NO==iValue) {
                return pair<int,int>(0,0);
        }
        if(*N==iValue) {
                return pair<int,int>(0,1);
        }
        if(*NE==iValue) {
                return pair<int,int>(0,2);
        }
        if(*O==iValue) {
                return pair<int,int>(1,0);
        }
        if(*C==iValue) {
                return pair<int,int>(1,1);
        }
        if(*E==iValue) {
                return pair<int,int>(1,2);
        }
        if(*SO==iValue) {
                return pair<int,int>(2,0);
        }
        if(*S==iValue) {
                return pair<int,int>(2,1);
        }
        if(*SE==iValue) {
                return pair<int,int>(2,2);
        }

        // if we did not found the value, raise invalid argument error

        throw std::invalid_argument("The value is not present in the region holder.");
}
