#ifndef TRIPLETRIPLEHOLDER_HPP
#define TRIPLETRIPLEHOLDER_HPP

#include "TripleHolder.hpp"
#include "RegionHolder.hpp"
#include <vector>

class TripleTripleHolder {

private:
        std::vector<TripleHolder> tripleHolders;

public:
        TripleTripleHolder(TripleHolder const &th1, TripleHolder const &th2, TripleHolder const &th3);
        TripleTripleHolder(RegionHolder const &rg);
        bool isConsistent() const;
};

#endif