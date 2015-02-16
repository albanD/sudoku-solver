#ifndef ONLYONECHOICEINROWVISITOR
#define ONLYONECHOICEINROWVISITOR

#include "IVisitor.hpp"
#include "Grid.hpp"
#include "LastCellFinder.hpp"

class OnlyOneChoiceInRowVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInRowVisitor();
};

#endif