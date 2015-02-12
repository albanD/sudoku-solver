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



bool OnlyOneChoiceInColumnVisitor::Visit(Grid &ioGrid) const{

        bool changed = false;

        LastCellFinder lf1(ioGrid.NO().leftColumn(),
                           ioGrid.O().leftColumn(),
                           ioGrid.SO().leftColumn());
        changed |= lf1.fill();

        LastCellFinder lf2(ioGrid.NO().middleColumn(),
                           ioGrid.O().middleColumn(),
                           ioGrid.SO().middleColumn());
        changed |= lf2.fill();

        LastCellFinder lf3(ioGrid.NO().rightColumn(),
                           ioGrid.O().rightColumn(),
                           ioGrid.SO().rightColumn());
        changed |= lf3.fill();

        LastCellFinder lf4(ioGrid.N().leftColumn(),
                           ioGrid.C().leftColumn(),
                           ioGrid.S().leftColumn());
        changed |= lf4.fill();

        LastCellFinder lf5(ioGrid.N().middleColumn(),
                           ioGrid.C().middleColumn(),
                           ioGrid.S().middleColumn());
        changed |= lf5.fill();

        LastCellFinder lf6(ioGrid.N().rightColumn(),
                           ioGrid.C().rightColumn(),
                           ioGrid.S().rightColumn());
        changed |= lf6.fill();

        LastCellFinder lf7(ioGrid.NE().leftColumn(),
                           ioGrid.E().leftColumn(),
                           ioGrid.SE().leftColumn());
        changed |= lf7.fill();

        LastCellFinder lf8(ioGrid.NE().middleColumn(),
                           ioGrid.E().middleColumn(),
                           ioGrid.SE().middleColumn());
        changed |= lf8.fill();

        LastCellFinder lf9(ioGrid.NE().rightColumn(),
                           ioGrid.E().rightColumn(),
                           ioGrid.SE().rightColumn());
        changed |= lf9.fill();

        return changed;

}

OnlyOneChoiceInColumnVisitor::OnlyOneChoiceInColumnVisitor(){};


bool OnlyOneChoiceInRegionVisitor::Visit(Grid &ioGrid) const{

        bool changed = false;

        LastCellFinder lf1(ioGrid.NO().leftColumn(),
                           ioGrid.NO().middleColumn(),
                           ioGrid.NO().rightColumn());
        changed |= lf1.fill();

        LastCellFinder lf2(ioGrid.N().leftColumn(),
                           ioGrid.N().middleColumn(),
                           ioGrid.N().rightColumn());
        changed |= lf2.fill();

        LastCellFinder lf3(ioGrid.NE().leftColumn(),
                           ioGrid.NE().middleColumn(),
                           ioGrid.NE().rightColumn());
        changed |= lf3.fill();

        LastCellFinder lf4(ioGrid.O().leftColumn(),
                           ioGrid.O().middleColumn(),
                           ioGrid.O().rightColumn());
        changed |= lf4.fill();

        LastCellFinder lf5(ioGrid.C().leftColumn(),
                           ioGrid.C().middleColumn(),
                           ioGrid.C().rightColumn());
        changed |= lf5.fill();

        LastCellFinder lf6(ioGrid.E().leftColumn(),
                           ioGrid.E().middleColumn(),
                           ioGrid.E().rightColumn());
        changed |= lf6.fill();

        LastCellFinder lf7(ioGrid.SO().leftColumn(),
                           ioGrid.SO().middleColumn(),
                           ioGrid.SO().rightColumn());
        changed |= lf7.fill();

        LastCellFinder lf8(ioGrid.S().leftColumn(),
                           ioGrid.S().middleColumn(),
                           ioGrid.S().rightColumn());
        changed |= lf8.fill();

        LastCellFinder lf9(ioGrid.SE().leftColumn(),
                           ioGrid.SE().middleColumn(),
                           ioGrid.SE().rightColumn());
        changed |= lf9.fill();

        return changed;

}

OnlyOneChoiceInRegionVisitor::OnlyOneChoiceInRegionVisitor(){};
