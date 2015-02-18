#include <vector>
#include "TripleTripleHolder.hpp"
#include "RegionHolder.hpp"
#include "TripleHolder.hpp"
#include <iostream>
using namespace std;


TripleTripleHolder::TripleTripleHolder(RegionHolder const &rh) {
        for(int i=0; i<3; ++i) {
                tripleHolders.push_back(rh.getRow(i));
        }
}

TripleTripleHolder::TripleTripleHolder(TripleHolder const &th1, TripleHolder const &th2, TripleHolder const &th3) {
        tripleHolders.push_back(th1);
        tripleHolders.push_back(th2);
        tripleHolders.push_back(th3);
}

bool TripleTripleHolder::isConsistent() const{
        std::vector<bool> isPresent = std::vector<bool>(9, false);

        for(int i=0; i<3; ++i) {
                for(int j=0; j<3; ++j) {
                        // if there is nothing in the cell, discard it
                        if(tripleHolders[i].getCell(j).value==0) {
                                continue;
                        }

                        // check if the value has already been seen or if its the first time
                        if(isPresent[tripleHolders[i].getCell(j).value-1]) {
                                return false;
                        } else {
                                isPresent[tripleHolders[i].getCell(j).value-1] = true;
                        }
                }
        }

        return true;
}

void TripleTripleHolder::flagValues(ValueEliminator &ve) {
        for(int i=0; i<3; ++i) {
                tripleHolders[i].flagValues(ve);
        }
}