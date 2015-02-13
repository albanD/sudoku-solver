#ifndef LAST_CELL_FINDER
#define LAST_CELL_FINDER

#include "Holder.hpp"
#include <vector>

using namespace std;

class LastCellFinder{
private:
        vector<TripleHolder> holders;

public:
        LastCellFinder(TripleHolder h1, TripleHolder h2, TripleHolder h3);
        bool fill();
};


#endif
