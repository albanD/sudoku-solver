#ifndef ONLYONECHOICEINROWVISITOR_HPP
#define ONLYONECHOICEINROWVISITOR_HPP

#include "IVisitor.hpp"
#include "Grid.hpp"

class OnlyOneChoiceInRowVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInRowVisitor();
};

#endif