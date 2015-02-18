#include "OnlySquareVisitor.hpp"


bool OnlySquareVisitor::Visit(Grid &ioGrid) const{
        bool changed_something = false;

        unordered_set<int> fpossibilities, spossibilities, availables;

        // Only Square on each row
        for(int row=0; row<9; ++row){
                // ensure that the rule is applicable
                ValueEliminator ve = rowPossibilities(row, ioGrid);
                if(ve.availableValues()!=2){continue;}

                // Find the positions of the two empties in the Row
                int fc, sc;
                for(fc=0;fc<9;++fc){
                        if(ioGrid.getCell(row, fc).isEmpty()){
                                break;
                        }
                }
                for(sc=fc+1;sc<9;++sc){
                        if(ioGrid.getCell(row,sc).isEmpty()){
                                break;
                        }
                }

                // Find the possible values according to the other constraints
                int freg_index = (row/3)*3 + (fc/3);
                fpossibilities = intersection(colPossibilities(fc, ioGrid).availableValue(),
                                                                 regPossibilities(freg_index, ioGrid).availableValue());
                int sreg_index = (row/3)*3 + (sc/3);
                spossibilities = intersection(colPossibilities(sc, ioGrid).availableValue(),
                                                                 regPossibilities(sreg_index, ioGrid).availableValue());

                // Figure out if one Cell cannot take one of the row's missing value-> she must take the other
                bool changed_one = false;
                availables = ve.availableValue();
                for(unordered_set<int>::iterator it=availables.begin(), end=availables.end(); it!=end;it++){
                        // Check if we are in a valid state
                        if((fpossibilities.count(*it)==0) && (spossibilities.count(*it)==0)) {
                                throw InvalidGridException();
                        }

                        if(fpossibilities.count(*it)==0){ //we cannot put this value in first
                                ioGrid.getCell(row, sc) = *it; //so we put it in second
                                availables.erase(*it); // remove it from the set, so that only the other remains
                                changed_one = true;
                                break;
                        }
                        if(spossibilities.count(*it)==0){ //we cannot put this value in second
                                ioGrid.getCell(row, fc) = *it;
                                availables.erase(*it);
                                changed_one = true;
                                break;
                        }
                }

                // If we manage to set one, we can set the other with the remaining value
                if(changed_one){
                        int last_missing_value = *(availables.begin());
                        // Check if we are in a valid state
                        if((fpossibilities.count(last_missing_value)==0) && (spossibilities.count(last_missing_value)==0)) {
                                throw InvalidGridException();
                        }
                        if(ioGrid.getCell(row,fc).isEmpty()){ //The first is the one that didn't get filled
                                ioGrid.getCell(row,fc)=last_missing_value;
                        } else {
                                ioGrid.getCell(row,sc)=last_missing_value;
                        }
                }
                changed_something|= changed_one;
        }

        // Only Square on each Column
        for(int col=0; col<9; ++col){
                // ensure that the rule is applicable
                ValueEliminator ve = colPossibilities(col, ioGrid);
                if(ve.availableValues()!=2){continue;}

                // Find the positions of the two empties in the Column
                int fr, sr;
                for(fr=0;fr<9;++fr){
                        if(ioGrid.getCell(fr, col).isEmpty()){
                                break;
                        }
                }
                for(sr=fr+1;sr<9;++sr){
                        if(ioGrid.getCell(sr, col).isEmpty()){
                                break;
                        }
                }

                // Find the possible values according to the other constraints
                int freg_index = (fr/3)*3 + (col/3);
                fpossibilities = intersection(rowPossibilities(fr, ioGrid).availableValue(),
                                                                 regPossibilities(freg_index, ioGrid).availableValue());
                int sreg_index = (sr/3)*3 + (col/3);
                spossibilities = intersection(rowPossibilities(sr, ioGrid).availableValue(),
                                                                 regPossibilities(sreg_index, ioGrid).availableValue());

                // Figure out if one Cell cannot take one of the Column's missing value-> she must take the other
                bool changed_one = false;
                availables = ve.availableValue();
                for(unordered_set<int>::iterator it=availables.begin(), end=availables.end(); it!=end;it++){
                        // Check if we are in a valid state
                        if((fpossibilities.count(*it)==0) && (spossibilities.count(*it)==0)) {
                                throw InvalidGridException();
                        }

                        if(fpossibilities.count(*it)==0){ //we cannot put this value in first
                                ioGrid.getCell(sr, col) = *it; //so we put it in second
                                availables.erase(*it); // remove it from the set, so that only the other remains
                                changed_one = true;
                                break;
                        }
                        if(spossibilities.count(*it)==0){ //we cannot put this value in second
                                ioGrid.getCell(fr, col) = *it;
                                availables.erase(*it);
                                changed_one = true;
                                break;
                        }
                }

                // If we manage to set one, we can set the other with the remaining value
                if(changed_one){
                        int last_missing_value = *(availables.begin());
                        // Check if we are in a valid state
                        if((fpossibilities.count(last_missing_value)==0) && (spossibilities.count(last_missing_value)==0)) {
                                throw InvalidGridException();
                        }
                        if(ioGrid.getCell(fr,col).isEmpty()){ //The first is the one that didn't get filled
                                ioGrid.getCell(fr,col)=last_missing_value;
                        } else {
                                ioGrid.getCell(sr,col)=last_missing_value;
                        }
                }
                changed_something|= changed_one;
        }

        return changed_something;
}

unordered_set<int> OnlySquareVisitor::intersection(unordered_set<int> a, unordered_set<int> b){
        unordered_set<int> inter;
        for(unordered_set<int>::iterator it=a.begin(),end=a.end(); it!=end;++it){
                if(b.count(*it)!=0){
                        inter.insert(*it);
                }
        }
        return inter;
}

ValueEliminator OnlySquareVisitor::rowPossibilities(int row_index, Grid &ioGrid) const{
        ValueEliminator rve = ValueEliminator();
        int main_row = row_index / 3;
        int sub_row = row_index - 3*main_row;
        for(int mc=0; mc<3; ++mc){
                RowHolder r = ioGrid.getRegion(3*main_row + mc).getRow(sub_row);
                r.flagValues(rve);
        }
        return rve;
}

ValueEliminator OnlySquareVisitor::colPossibilities(int col_index, Grid &ioGrid) const{
        ValueEliminator cve = ValueEliminator();
        int main_col = col_index / 3;
        int sub_col = col_index - 3*main_col;
        for(int mr=0; mr<3; ++mr){
                ColumnHolder c = ioGrid.getRegion(main_col +3*mr).getColumn(sub_col);
                c.flagValues(cve);
        }
        return cve;
}

ValueEliminator OnlySquareVisitor::regPossibilities(int reg_index, Grid &ioGrid) const{
        ValueEliminator rve = ValueEliminator();
        RegionHolder rh = ioGrid.getRegion(reg_index);
        rh.flagValues(rve);
        return rve;
}


OnlySquareVisitor::OnlySquareVisitor(){}
