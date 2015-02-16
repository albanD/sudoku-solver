#ifndef VISITORS
#define VISITORS

#include "Grid.hpp"

class IVisitor{
public:
        virtual ~IVisitor(){};
        virtual bool Visit(Grid &ioGrid) const =0;
};

#endif
