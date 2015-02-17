#ifndef FILLANYSUREVISITOR_HPP
#define FILLANYSUREVISITOR_HPP


#include "IVisitor.hpp"
#include "Grid.hpp"

class FillAnySureVisitor : public IVisitor {
public:
        FillAnySureVisitor();
        virtual bool Visit(Grid &ioGrid) const;

};

#endif
