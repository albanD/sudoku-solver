#ifndef LAST_CELL_FINDER
#define LAST_CELL_FINDER

#include "Holder.hpp"
#include <array>

using namespace std;

class LastCellFinder{
private:
        array<TripleHolder,3> holders;

public:
        LastCellFinder(TripleHolder h1, TripleHolder h2, TripleHolder h3);
        bool fill();
};


#endif
