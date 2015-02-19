#ifndef LAST_CELL_FINDER_HPP
#define LAST_CELL_FINDER_HPP

#include <vector>

#include "TripleHolder.hpp"

class LastCellFinder{
private:
        std::vector<TripleHolder> holders;

public:
        LastCellFinder(TripleHolder h1, TripleHolder h2, TripleHolder h3);
        bool fill();
};


#endif
