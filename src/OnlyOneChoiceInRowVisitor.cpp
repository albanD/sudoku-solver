#include "OnlyOneChoiceInRowVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
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

