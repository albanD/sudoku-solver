#include "OnlyOneChoiceInColumnVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include "LastCellFinder.hpp"

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
