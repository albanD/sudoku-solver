#include "Grid.hpp"
#ifndef VISITORS
#define VISITORS

class IVisitor{
public:
        virtual ~IVisitor(){};
        virtual bool Visit(Grid &ioGrid) const =0;
};

class OnlyOneChoiceInRowVisitor : public IVisitor{
        virtual bool Visit(Grid &ioGrid) const;
};

#endif
