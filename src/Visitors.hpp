#ifndef VISITORS
#define VISITORS

class IVisitor{
public:
        virtual ~IVisitor(){};
        virtual bool Visit(Grid &ioGrid) const =0;
};


#endif
