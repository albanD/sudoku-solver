#include "TwoOutOfThreeRowVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include <vector>
#include <iostream>
using namespace std;

TwoOutOfThreeRowVisitor::TwoOutOfThreeRowVisitor(){}

bool TwoOutOfThreeRowVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<bool> presentInTriplet;
        pair<int,int> position;
        int line;
        std::vector<bool>::iterator it;
        TripleHolder fillableTriplet;

        for(int main_row=0; main_row<3;++main_row) {
                // main_row is the row we are working with

                for(int main_col=0; main_col<3; ++main_col) {
                        // main_col is the column in the main_row we are trying to fill
                        // we place this working region in regions[0]
                        regions = std::vector<RegionHolder>();
                        regions.push_back(ioGrid.getRegion(3*main_row + (main_col+0)%3));
                        regions.push_back(ioGrid.getRegion(3*main_row + (main_col+1)%3));
                        regions.push_back(ioGrid.getRegion(3*main_row + (main_col+2)%3));
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                
                                // if this value is already set, discard this value for this region
                                if(regions[0].isValuePresent(value)){continue;}

                                // if the two other regions in main_row contains the value, continue
                                if(regions[1].isValuePresent(value) && regions[2].isValuePresent(value)) {

                                        // find the line where it should be
                                        presentInTriplet = vector<bool>(3, false);
                                        position = regions[1].valuePosition(value);
                                        presentInTriplet[position.first] = true;
                                        position = regions[2].valuePosition(value);
                                        presentInTriplet[position.first] = true;

                                        line=0;
                                        it = presentInTriplet.begin();
                                        while(*it) {
                                                ++it;
                                                ++line;
                                        }


                                        // find the column where it should be
                                        presentInTriplet = vector<bool>(3, false);
 
                                        // is there this value already in this column?
                                        for(int i=0; i<3; ++i) {
                                                // for each column
                                                for(int j=1; j<3; ++j) {
                                                        // for each other region in the column
                                                        presentInTriplet[i] = presentInTriplet[i] || ioGrid.getRegion(3*((main_row+1)%3) + (main_col+0)%3).getColumn(i).isValuePresent(value);
                                                }
                                        }
                                                        
                                        
                                        // get the possible column in the working region                                        
                                        if(line == 0) {
                                                fillableTriplet = regions[0].topRow();
                                        } else if (line == 1) {
                                                fillableTriplet = regions[0].middleRow();
                                        } else if (line == 2) {
                                                fillableTriplet = regions[0].bottomRow();
                                        }

                                        // is there a value in this possible cell?
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
