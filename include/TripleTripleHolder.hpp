#ifndef TRIPLETRIPLEHOLDER_HPP
#define TRIPLETRIPLEHOLDER_HPP

#include <vector>

#include "TripleHolder.hpp"
#include "RegionHolder.hpp"
#include "ValueEliminator.hpp"

class TripleTripleHolder {

private:
        std::vector<TripleHolder> tripleHolders;

public:
        TripleTripleHolder(TripleHolder const &th1, TripleHolder const &th2, TripleHolder const &th3);
        TripleTripleHolder(RegionHolder const &rg);
        bool isConsistent() const;

        void flagValues(ValueEliminator &ve);
};

#endif