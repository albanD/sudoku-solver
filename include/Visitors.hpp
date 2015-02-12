#include "Grid.hpp"
#ifndef VISITORS
#define VISITORS

class IVisitor{
public:
        virtual ~IVisitor(){};
        virtual bool Visit(Grid &ioGrid) const =0;
};

class OnlyOneChoiceInRowVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInRowVisitor();
};

class OnlyOneChoiceInColumnVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInColumnVisitor();
};

class OnlyOneChoiceInRegionVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlyOneChoiceInRegionVisitor();
};


#endif
