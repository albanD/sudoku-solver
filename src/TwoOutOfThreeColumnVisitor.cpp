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
                // main_col is the column we are working with
                
                for(int main_row=0; main_row<3; ++main_row) {
                        // main_row is the position of the row of the region we are trying to fill in main_col
                        // we place this working region in regions[0]
                        regions = std::vector<RegionHolder>();
                        regions.push_back(ioGrid.getRegion(3*((main_row+0)%3) + main_col));
                        regions.push_back(ioGrid.getRegion(3*((main_row+1)%3) + main_col));
                        regions.push_back(ioGrid.getRegion(3*((main_row+2)%3) + main_col));
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                
                                // if the value is already set in the working region, stop here
                                if(regions[0].isValuePresent(value)){continue;}

                                // continue only if the value is present in the two other regions in this column
                                if(regions[1].isValuePresent(value) && regions[2].isValuePresent(value)) {
                                        // find the column where value should be in the working region
                                        
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


                                        // find the line where it can be in the selected column
                                        
                                        presentInTriplet = vector<bool>(3, false);
                                        
                                        // cannot be on the same line as a the same value in another region from the same row
                                        for(int i=0; i<3; ++i) {
                                                // for each line
                                                for(int j=1; j<3; ++j) {
                                                        // for each other region in the row
                                                        presentInTriplet[i] = presentInTriplet[i] || ioGrid.getRegion(3*((main_row+0)%3) + (main_col+j)%3).getRow(i).isValuePresent(value);
                                                }
                                        }

                                        // Cannot be in a cell where there is already an element
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
