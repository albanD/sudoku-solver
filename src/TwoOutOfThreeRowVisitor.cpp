#include <vector>

#include "TwoOutOfThreeRowVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include "TripleHolder.hpp"


TwoOutOfThreeRowVisitor::TwoOutOfThreeRowVisitor(){}

bool TwoOutOfThreeRowVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<bool> presentInTriplet;
        std::pair<int,int> position;
        int line, i;
        std::vector<bool>::iterator it;

        for(int main_row=0; main_row<3;++main_row) {
                // main_row is the row we are working with

                for(int main_col=0; main_col<3; ++main_col) {
                        // main_col is the column in the main_row we are trying to fill
                        // we place this working region in regions[0]
                        regions = std::vector<RegionHolder>();
                        for(i=0; i<3; ++i) {
                                regions.push_back(ioGrid.getRegion(3*main_row + (main_col+i)%3));
                        }
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                
                                // if this value is already set, discard this value for this region
                                if(regions[0].isValuePresent(value)){continue;}

                                // if the two other regions in main_row contains the value, continue
                                if(regions[1].isValuePresent(value) && regions[2].isValuePresent(value)) {
                                        
                                        // find the line where it should be
                                        presentInTriplet = std::vector<bool>(3, false);
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
                                        presentInTriplet = std::vector<bool>(3, false);
 
                                        // is there this value already in this column?
                                        for(i=0; i<3; ++i) {
                                                // for each column
                                                for(int j=1; j<3; ++j) {
                                                        // for each other region in the column
                                                        presentInTriplet[i] = presentInTriplet[i] || ioGrid.getRegion(3*((main_row+j)%3) + (main_col+0)%3).getColumn(i).isValuePresent(value);
                                                }
                                        }
                                                        
                                        
                                        // get the possible row in the working region                                        
                                        TripleHolder fillableTriplet = regions[0].getRow(line);

                                        // is there a value in the cells of the possible row?
                                        for(i=0; i<3; ++i) {
                                                // each line
                                                if(!fillableTriplet.getCell(i).isEmpty()) {
                                                        presentInTriplet[i] = true;
                                                }
                                        }

                                        // if there is only one possile place, fill it
                                        for(i=0; i<3; ++i) {
                                                if(!presentInTriplet[(i+0)%3] && presentInTriplet[(i+1)%3] && presentInTriplet[(i+2)%3]) {
                                                        fillableTriplet.getCell(i) = value;
                                                        changed = true;
                                                }
                                        }

                                }
                        }
                } 
              
        }
        return changed;
}
