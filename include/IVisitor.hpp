#ifndef VISITORS_HPP
#define VISITORS_HPP

#include "Grid.hpp"

class IVisitor{
public:
        virtual ~IVisitor(){};
        virtual bool Visit(Grid &ioGrid) const =0;
};

#endif
