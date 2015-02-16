#ifndef ONLYONECHOICEINREGIONVISITOR
#define ONLYONECHOICEINREGIONVISITOR

#include "IVisitor.hpp"
#include "Grid.hpp"
#include "LastCellFinder.hpp"

class OnlyOneChoiceInRegionVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInRegionVisitor();
};

#endif