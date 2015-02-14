#include "Visitors.hpp"
#include "LastCellFinder.hpp"
#include <iostream>
using namespace std;

bool OnlyOneChoiceInRowVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;

        for(int main_row=0;main_row<3;++main_row){
                RegionHolder rh1 = ioGrid.getRegion(3* main_row);
                RegionHolder rh2 = ioGrid.getRegion(3* main_row + 1);
                RegionHolder rh3 = ioGrid.getRegion(3* main_row + 2);

                LastCellFinder lf1(rh1.topRow(),
                                   rh2.topRow(),
                                   rh3.topRow());
                changed |= lf1.fill();

                LastCellFinder lf2(rh1.middleRow(),
                                   rh2.middleRow(),
                                   rh3.middleRow());
                changed |= lf2.fill();

                LastCellFinder lf3(rh1.bottomRow(),
                                   rh2.bottomRow(),
                                   rh3.bottomRow());
                changed |= lf3.fill();
        }

        return changed;
}

OnlyOneChoiceInRowVisitor::OnlyOneChoiceInRowVisitor(){};



bool OnlyOneChoiceInColumnVisitor::Visit(Grid &ioGrid) const{

        bool changed = false;

        for(int main_col=0;main_col<3;++main_col){
                RegionHolder rh1 = ioGrid.getRegion(main_col);
                RegionHolder rh2 = ioGrid.getRegion(main_col+3);
                RegionHolder rh3 = ioGrid.getRegion(main_col+6);

                LastCellFinder lf1(rh1.leftColumn(),
                                   rh2.leftColumn(),
                                   rh3.leftColumn());
                changed |= lf1.fill();

                LastCellFinder lf2(rh1.middleColumn(),
                                   rh2.middleColumn(),
                                   rh3.middleColumn());
                changed |= lf2.fill();

                LastCellFinder lf3(rh1.rightColumn(),
                                   rh2.rightColumn(),
                                   rh3.rightColumn());
                changed |= lf3.fill();
        }

        return changed;

}

OnlyOneChoiceInColumnVisitor::OnlyOneChoiceInColumnVisitor(){}


bool OnlyOneChoiceInRegionVisitor::Visit(Grid &ioGrid) const{

        bool changed = false;

        for(int region_index=0;region_index<9; ++region_index){
                RegionHolder rh = ioGrid.getRegion(region_index);
                LastCellFinder lf(rh.leftColumn(),
                                  rh.middleColumn(),
                                  rh.rightColumn());
                changed |= lf.fill();
        }

        return changed;
}

OnlyOneChoiceInRegionVisitor::OnlyOneChoiceInRegionVisitor(){}


bool OnlySquareVisitor::Visit(Grid &ioGrid) const{


        // Only Square on each row
        for(int row=0; row<9; ++row){
                // ensure that the rule is applicable
                ValueEliminator ve = rowPossibilities(row, ioGrid);
                if(ve.availableValues()!=2){continue;}

                // Find the positions of the two empties in the Row
                int fc, sc;
                for(fc=0;fc<9;++fc){
                        if(ioGrid.getCell(row, fc)->isEmpty()){
                                break;
                        }
                }
                for(sc=fc+1;sc<9;++sc){
                        if(ioGrid.getCell(row,sc)->isEmpty()){
                                break;
                        }
                }

                // Find the possible values according to the other constraints
                int freg_index = (row/3)*3 + (fc/3);
                unordered_set<int> fpossibilities = intersection(colPossibilities(fc, ioGrid).availableValue(),
                                                                 regPossibilities(freg_index, ioGrid).availableValue());
                int sreg_index = (row/3)*3 + (sc/3);
                unordered_set<int> spossibilities = intersection(colPossibilities(sc, ioGrid).availableValue(),
                                                                 regPossibilities(sreg_index, ioGrid).availableValue());

                // Figure out if one Cell cannot take one of the row's missing value-> she must take the other
                bool changed_one = false;
                unordered_set<int> availables = ve.availableValue();
                for(unordered_set<int>::iterator it=availables.begin(), end=availables.end(); it!=end;it++){
                        if(fpossibilities.count(*it)==0){ //we cannot put this value in first
                                *(ioGrid.getCell(row, sc)) = *it; //so we put it in second
                                availables.erase(*it); // remove it from the set, so that only the other remains
                                changed_one = true;
                                break;
                        }
                        if(spossibilities.count(*it)==0){ //we cannot put this value in second
                                *(ioGrid.getCell(row, fc)) = *it;
                                availables.erase(*it);
                                changed_one = true;
                                break;
                        }
                }

                // If we manage to set one, we can set the other with the remaining value
                if(changed_one){
                        int last_missing_value = *(availables.begin());
                        if(ioGrid.getCell(row,fc)->isEmpty()){ //The first is the one that didn't get filled
                                *(ioGrid.getCell(row,fc))=last_missing_value;
                        } else {
                                *(ioGrid.getCell(row,sc))=last_missing_value;
                        }
                }
        }

        // Only Square on each Column
        for(int col=0; col<9; ++col){
                // ensure that the rule is applicable
                ValueEliminator ve = colPossibilities(col, ioGrid);
                if(ve.availableValues()!=2){continue;}

                // Find the positions of the two empties in the Column
                int fr, sr;
                for(fr=0;fr<9;++fr){
                        if(ioGrid.getCell(fr, col)->isEmpty()){
                                break;
                        }
                }
                for(sr=fr+1;sr<9;++sr){
                        if(ioGrid.getCell(sr, col)->isEmpty()){
                                break;
                        }
                }

                // Find the possible values according to the other constraints
                int freg_index = (fr/3)*3 + (col/3);
                unordered_set<int> fpossibilities = intersection(rowPossibilities(fr, ioGrid).availableValue(),
                                                                 regPossibilities(freg_index, ioGrid).availableValue());
                int sreg_index = (sr/3)*3 + (col/3);
                unordered_set<int> spossibilities = intersection(rowPossibilities(sr, ioGrid).availableValue(),
                                                                 regPossibilities(sreg_index, ioGrid).availableValue());

                // Figure out if one Cell cannot take one of the Column's missing value-> she must take the other
                bool changed_one = false;
                unordered_set<int> availables = ve.availableValue();
                for(unordered_set<int>::iterator it=availables.begin(), end=availables.end(); it!=end;it++){
                        if(fpossibilities.count(*it)==0){ //we cannot put this value in first
                                *(ioGrid.getCell(sr, col)) = *it; //so we put it in second
                                availables.erase(*it); // remove it from the set, so that only the other remains
                                changed_one = true;
                                break;
                        }
                        if(spossibilities.count(*it)==0){ //we cannot put this value in second
                                *(ioGrid.getCell(fr, col)) = *it;
                                availables.erase(*it);
                                changed_one = true;
                                break;
                        }
                }

                // If we manage to set one, we can set the other with the remaining value
                if(changed_one){
                        int last_missing_value = *(availables.begin());
                        if(ioGrid.getCell(fr,col)->isEmpty()){ //The first is the one that didn't get filled
                                *(ioGrid.getCell(fr,col))=last_missing_value;
                        } else {
                                *(ioGrid.getCell(sr,col))=last_missing_value;
                        }
                }
        }

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
