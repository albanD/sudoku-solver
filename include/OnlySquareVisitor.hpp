#ifndef ONLYSQUAREVISITOR
#define ONLYSQUAREVISITOR

#include "IVisitor.hpp"
#include "Grid.hpp"

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