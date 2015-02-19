#ifndef ONLYONECHOICEINREGIONVISITOR_HPP
#define ONLYONECHOICEINREGIONVISITOR_HPP

#include "IVisitor.hpp"
#include "Grid.hpp"

class OnlyOneChoiceInRegionVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInRegionVisitor();
};

#endif