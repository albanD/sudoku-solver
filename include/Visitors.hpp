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

class OnlySquareVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlySquareVisitor();
private:
        static unordered_set<int> intersection(unordered_set<int> a, unordered_set<int> b);
        ValueEliminator rowPossibilities(int row_index, Grid &ioGrid) const;
        ValueEliminator colPossibilities(int col_index, Grid &ioGrid) const;
        ValueEliminator regPossibilities(int reg_index, Grid &ioGrid) const;
};
#endif
