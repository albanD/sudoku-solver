#ifndef TWOOUTOFTHREEROWVISITOR_HPP
#define TWOOUTOFTHREEROWVISITOR_HPP


#include "IVisitor.hpp"
#include "Grid.hpp"

class TwoOutOfThreeRowVisitor : public IVisitor {
public:
        TwoOutOfThreeRowVisitor();
        virtual bool Visit(Grid &ioGrid) const;

};

#endif
