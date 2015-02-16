#ifndef TWOOUTOFTHREERCOLUMNVISITOR_HPP
#define TWOOUTOFTHREECOLUMNVISITOR_HPP


#include "IVisitor.hpp"
#include "Grid.hpp"

class TwoOutOfThreeColumnVisitor : public IVisitor {
public:
        TwoOutOfThreeColumnVisitor();
        virtual bool Visit(Grid &ioGrid) const;

};

#endif
