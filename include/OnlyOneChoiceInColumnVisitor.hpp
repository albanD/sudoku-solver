#ifndef ONLYONECHOICEINCOLUMNVISITOR
#define ONLYONECHOICEINCOLUMNVISITOR

#include "IVisitor.hpp"
#include "Grid.hpp"
#include "LastCellFinder.hpp"

class OnlyOneChoiceInColumnVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInColumnVisitor();
};

#endif