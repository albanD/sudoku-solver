#include "OnlyOneChoiceInRegionVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include "LastCellFinder.hpp"


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
