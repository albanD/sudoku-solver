#ifndef ONLYSQUAREVISITOR_HPP
#define ONLYSQUAREVISITOR_HPP

#include <unordered_set>

#include "IVisitor.hpp"
#include "Grid.hpp"
#include "ValueEliminator.hpp"

class OnlySquareVisitor : public IVisitor{
public:
        virtual bool Visit(Grid &ioGrid) const;
        OnlySquareVisitor();
private:
        static std::unordered_set<int> intersection(std::unordered_set<int> a, std::unordered_set<int> b);
        ValueEliminator rowPossibilities(int row_index, Grid &ioGrid) const;
        ValueEliminator colPossibilities(int col_index, Grid &ioGrid) const;
        ValueEliminator regPossibilities(int reg_index, Grid &ioGrid) const;
};

#endif