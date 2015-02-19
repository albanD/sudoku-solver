#include <utility>
#include <vector>

#include "TwoOutOfThreeColumnVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include "TripleHolder.hpp"

TwoOutOfThreeColumnVisitor::TwoOutOfThreeColumnVisitor(){}

bool TwoOutOfThreeColumnVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<bool> presentInTriplet;
        std::pair<int,int> position;
        int col, i;
        std::vector<bool>::iterator it;

        for(int main_col=0; main_col<3;++main_col) {
                // main_col is the column we are working with
                
                for(int main_row=0; main_row<3; ++main_row) {
                        // main_row is the position of the row of the region we are trying to fill in main_col
                        // we place this working region in regions[0]
                        regions = std::vector<RegionHolder>();
                        for(i=0; i<3; ++i) {
                                regions.push_back(ioGrid.getRegion(3*((main_row+i)%3) + main_col));
                        }
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                
                                // if the value is already set in the working region, stop here
                                if(regions[0].isValuePresent(value)){continue;}

                                // continue only if the value is present in the two other regions in this column
                                if(regions[1].isValuePresent(value) && regions[2].isValuePresent(value)) {
                                        // find the column where value should be in the working region
                                        
                                        presentInTriplet = std::vector<bool>(3, false);
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
                                        
                                        presentInTriplet = std::vector<bool>(3, false);
                                        
                                        // cannot be on the same line as a the same value in another region from the same row
                                        for(i=0; i<3; ++i) {
                                                // for each line
                                                for(int j=1; j<3; ++j) {
                                                        // for each other region in the row
                                                        presentInTriplet[i] = presentInTriplet[i] || ioGrid.getRegion(3*((main_row+0)%3) + (main_col+j)%3).getRow(i).isValuePresent(value);
                                                }
                                        }

                                        // Cannot be in a cell where there is already an element
                                        TripleHolder fillableTriplet = regions[0].getColumn(col);

                                        // is there a value in the cells of the possible column?
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
