#include "FillAnySureVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include <vector>

FillAnySureVisitor::FillAnySureVisitor(){}


// For local use only
pair<int,int> findOnlyOneNegative(std::vector<std::vector<bool>> impossibles);

bool FillAnySureVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<std::vector<bool>> impossibles;
        std::vector<bool> presentInColumns;
        pair<int,int> position;
        int col, i;
        std::vector<bool>::iterator it;

        for(int main_col=0; main_col<3;++main_col) {
                // go through columns
                
                for(int main_row=0; main_row<3; ++main_row) {
                        // go through rows

                        // set the working region in regions[0]
                        regions = std::vector<RegionHolder>();
                        regions.push_back(ioGrid.getRegion(3*((main_row+0)%3) + main_col));
                        regions.push_back(ioGrid.getRegion(3*((main_row+1)%3) + main_col));
                        regions.push_back(ioGrid.getRegion(3*((main_row+2)%3) + main_col));
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                
                                // if value is in working region skip it
                                if(regions[0].isValuePresent(value)){continue;}

                                // find the col where it can be
                                
                                presentInColumns = vector<bool>(3, false);
                                try {
                                        position = regions[1].valuePosition(value);
                                        presentInColumns[position.second] = true;
                                } catch( invalid_argument const &e) {}
                                try {
                                        position = regions[2].valuePosition(value);
                                        presentInColumns[position.second] = true;
                                } catch( invalid_argument const &e) {}



                                // find the rows where it should be and fill a 3x3 array of bool
                                // with true if cannot be at this place, false if possible
                                impossibles = std::vector<std::vector<bool>>();
                                for(int j=0; j<3; ++j) {
                                        // j is the possible columns in the working region

                                        // if the columns already have this value from another Region, pass
                                        if(presentInColumns[j]) {
                                                impossibles.push_back(vector<bool>(3, true));
                                                continue;
                                        } else {
                                                impossibles.push_back(vector<bool>(3, false));
                                        }
                                        
                                        // Possible or not due to the value in another column of main_row
                                        for(i=0; i<3; ++i) {
                                                // for each line
                                                for(int k=1; k<3; ++k) {
                                                        // for each other region in the row
                                                        impossibles[j][i] = impossibles[j][i] || ioGrid.getRegion(3*((main_row+0)%3) + (main_col+k)%3).getRow(i).isValuePresent(value);
                                                }
                                        }

                                        // get the triplet corresponding to j
                                        TripleHolder fillableTriplet = regions[0].getColumn(j);

                                        // Cannot be place in cells that are not empty
                                        for(i=0; i<3; ++i) {
                                                // each line
                                                if(!fillableTriplet.getCell(i).isEmpty()) {
                                                        impossibles[j][i] = true;
                                                }
                                        }
                                }

                                // If there is only one possible position where it could be, place it
                                try {
                                        position = findOnlyOneNegative(impossibles);
                                        if (position.first!=-1) {
                                                regions[0].getColumn(position.first).getCell(position.second) = value;

                                                ++changed;
                                        }
                                } catch( invalid_argument const &e) {}
                        }
                } 


                
        }
        return changed;
}

pair<int,int> findOnlyOneNegative(std::vector<std::vector<bool>> impossibles) {
        pair<int,int> position(-1,-1);

        int totalNegative = 0;
        for(int i=0; i<3; ++i) {
                for(int j=0; j<3; ++j) {
                        if(impossibles[i][j] == false) {
                                totalNegative += 1;
                                position = pair<int,int>(i,j);
                        }
                }
        }

        if(totalNegative == 1) {
                return position;
        }

        throw std::invalid_argument("The value is not present in the region holder.");
}