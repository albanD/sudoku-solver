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

        Cell & getNO() const;
        Cell & getN() const;
        Cell & getNE() const;
        Cell & getO() const;
        Cell & getC() const;
        Cell & getE() const;
        Cell & getSO() const;
        Cell & getS() const;
        Cell & getSE() const;
        Cell & getCell(int const cell_index) const;

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
        bool isFull() const;
        pair<int,int> valuePosition(unsigned char iValue) const;
        
private:
        Cell & NO;
        Cell & N;
        Cell & NE;
        Cell & O;
        Cell & C;
        Cell & E;
        Cell & SO;
        Cell & S;
        Cell & SE;
};



#endif
