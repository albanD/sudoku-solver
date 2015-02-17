#include "TwoOutOfThreeColumnVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include <vector>
#include <iostream>
using namespace std;

TwoOutOfThreeColumnVisitor::TwoOutOfThreeColumnVisitor(){}

bool TwoOutOfThreeColumnVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<bool> presentInTriplet;
        pair<int,int> position;
        int col;
        std::vector<bool>::iterator it;
        TripleHolder fillableTriplet;

        for(int main_col=0; main_col<3;++main_col) {
                // vertical
                
                for(int i=0; i<3; ++i) {
                        // work with the ith region in this row
                        regions = std::vector<RegionHolder>();
                        regions.push_back(ioGrid.getRegion(3*((i+0)%3) + main_col));
                        regions.push_back(ioGrid.getRegion(3*((i+1)%3) + main_col));
                        regions.push_back(ioGrid.getRegion(3*((i+2)%3) + main_col));
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                //
                                if(regions[0].isValuePresent(value)){continue;}

                                if(regions[1].isValuePresent(value) && regions[2].isValuePresent(value)) {
                                        // value is not present in the ith region
                                        // find the col where it should be
                                        
                                        presentInTriplet = vector<bool>(3, false);
                                        position = regions[1].valuePosition(value);
                                        presentInTriplet[position.second] = true;
                                        position = regions[2].valuePosition(value);
                                        presentInTriplet[position.second] = true;

                                        col=0;
                                        it = presentInTriplet.begin();
                                        while(*it) {
                                                ++it;
                                                ++col;
                                        }


                                        // find the column where it should be
                                        
                                        presentInTriplet = vector<bool>(3, false);
                                        
                                        presentInTriplet[0] = ioGrid.getRegion(3*((i+0)%3) + (main_col+1)%3).topRow().isValuePresent(value) || ioGrid.getRegion(3*((i+0)%3) + (main_col+2)%3).topRow().isValuePresent(value); 
                                        presentInTriplet[1] = ioGrid.getRegion(3*((i+0)%3) + (main_col+1)%3).middleRow().isValuePresent(value) || ioGrid.getRegion(3*((i+0)%3) + (main_col+2)%3).middleRow().isValuePresent(value); 
                                        presentInTriplet[2] = ioGrid.getRegion(3*((i+0)%3) + (main_col+1)%3).bottomRow().isValuePresent(value) || ioGrid.getRegion(3*((i+0)%3) + (main_col+2)%3).bottomRow().isValuePresent(value); 
                                        // Cannot be place in cells that are not empty
                                        
                                        if(col == 0) {
                                                fillableTriplet = regions[0].leftColumn();
                                        } else if (col == 1) {
                                                fillableTriplet = regions[0].middleColumn();
                                        } else if (col == 2) {
                                                fillableTriplet = regions[0].rightColumn();
                                        }

                                        if(!fillableTriplet.getFirst()->isEmpty()) {
                                                presentInTriplet[0] = true;
                                        }
                                        if(!fillableTriplet.getSecond()->isEmpty()) {
                                                presentInTriplet[1] = true;
                                        }
                                        if(!fillableTriplet.getThird()->isEmpty()) {
                                                presentInTriplet[2] = true;
                                        }

                                        // if there is only one possile place, fill it

                                        if(!presentInTriplet[0] && presentInTriplet[1] && presentInTriplet[2]) {
                                                *(fillableTriplet.getFirst()) = value;
                                                changed = true;
                                        }
                                        if(presentInTriplet[0] && !presentInTriplet[1] && presentInTriplet[2]) {
                                                *(fillableTriplet.getSecond()) = value;
                                                changed = true;
                                        }
                                        if(presentInTriplet[0] && presentInTriplet[1] && !presentInTriplet[2]) {
                                                *(fillableTriplet.getThird()) = value;
                                                changed = true;
                                        }

                                }
                        }
                } 


                
        }
        return changed;
}
