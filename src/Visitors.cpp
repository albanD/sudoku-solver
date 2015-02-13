#include "Visitors.hpp"
#include "LastCellFinder.hpp"


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


}


OnlySquareVisitor::OnlySquareVisitor(){}
