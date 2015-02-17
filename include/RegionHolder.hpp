#ifndef REGIONHOLDER_HPP
#define REGIONHOLDER_HPP

#include "Cell.hpp"
#include "RowHolder.hpp"
#include "ColumnHolder.hpp"
#include "Region.hpp"
#include "ValueEliminator.hpp"

class RegionHolder{
public:
        RegionHolder(Region &region);

        Cell* const getNO() const;
        Cell* const getN() const;
        Cell* const getNE() const;
        Cell* const getO() const;
        Cell* const getC() const;
        Cell* const getE() const;
        Cell* const getSO() const;
        Cell* const getS() const;
        Cell* const getSE() const;
        Cell* const getCell(int const cell_index) const;

        RowHolder topRow() const;
        RowHolder middleRow() const;
        RowHolder bottomRow() const;
        RowHolder getRow(int const row_idx) const;

        ColumnHolder leftColumn() const;
        ColumnHolder middleColumn() const;
        ColumnHolder rightColumn() const;
        ColumnHolder getColumn(int const col_idx) const;

        void flagValues(ValueEliminator &ve) const;
        bool isValuePresent(unsigned char iValue) const;
        pair<int,int> valuePosition(unsigned char iValue) const;
        
private:
        Cell* const NO;
        Cell* const N;
        Cell* const NE;
        Cell* const O;
        Cell* const C;
        Cell* const E;
        Cell* const SO;
        Cell* const S;
        Cell* const SE;
};



#endif
