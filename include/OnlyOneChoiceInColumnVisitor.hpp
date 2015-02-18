#ifndef ONLYONECHOICEINCOLUMNVISITOR_HPP
#define ONLYONECHOICEINCOLUMNVISITOR_HPP

#include "IVisitor.hpp"
#include "Grid.hpp"

class OnlyOneChoiceInColumnVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInColumnVisitor();
};

#endif