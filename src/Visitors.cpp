#include "Visitors.hpp"
#include "LastCellFinder.hpp"


bool OnlyOneChoiceInRowVisitor::Visit(Grid &ioGrid) const{

        bool changed = false;

        LastCellFinder lf1(ioGrid.NO().topRow(),
                           ioGrid.N().topRow(),
                           ioGrid.NE().topRow());
        changed |= lf1.fill();

        LastCellFinder lf2(ioGrid.NO().middleRow(),
                           ioGrid.N().middleRow(),
                           ioGrid.NE().middleRow());
        changed |= lf2.fill();

        LastCellFinder lf3(ioGrid.NO().bottomRow(),
                           ioGrid.N().bottomRow(),
                           ioGrid.NE().bottomRow());
        changed |= lf3.fill();

        LastCellFinder lf4(ioGrid.O().topRow(),
                           ioGrid.C().topRow(),
                           ioGrid.E().topRow());
        changed |= lf4.fill();

        LastCellFinder lf5(ioGrid.O().middleRow(),
                           ioGrid.C().middleRow(),
                           ioGrid.E().middleRow());
        changed |= lf5.fill();

        LastCellFinder lf6(ioGrid.O().bottomRow(),
                           ioGrid.C().bottomRow(),
                           ioGrid.E().bottomRow());
        changed |= lf6.fill();

        LastCellFinder lf7(ioGrid.SO().topRow(),
                           ioGrid.S().topRow(),
                           ioGrid.SE().topRow());
        changed |= lf7.fill();

        LastCellFinder lf8(ioGrid.SO().middleRow(),
                           ioGrid.S().middleRow(),
                           ioGrid.SE().middleRow());
        changed |= lf8.fill();

        LastCellFinder lf9(ioGrid.SO().bottomRow(),
                           ioGrid.S().bottomRow(),
                           ioGrid.SE().bottomRow());
        changed |= lf9.fill();

        return changed;

}

OnlyOneChoiceInRowVisitor::OnlyOneChoiceInRowVisitor(){};
