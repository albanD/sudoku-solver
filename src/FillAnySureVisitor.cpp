#include "FillAnySureVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include <vector>

FillAnySureVisitor::FillAnySureVisitor(){}


// For local use only
pair<int,int> findOnlyOneNegative(std::vector<std::vector<bool>> possibles);

bool FillAnySureVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<std::vector<bool>> possibles;
        std::vector<bool> possibleColumns;
        pair<int,int> position;
        int col;
        std::vector<bool>::iterator it;
        TripleHolder fillableTriplet;

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
                                
                                possibleColumns = vector<bool>(3, false);
                                try {
                                        position = regions[1].valuePosition(value);
                                        possibleColumns[position.second] = true;
                                } catch( invalid_argument const &e) {}
                                try {
                                        position = regions[2].valuePosition(value);
                                        possibleColumns[position.second] = true;
                                } catch( invalid_argument const &e) {}



                                // find the rows where it should be and fill a 3x3 array of bool
                                // with true if cannot be at this place, false if possible
                                possibles = std::vector<std::vector<bool>>();
                                for(int j=0; j<3; ++j) {
                                        // j is the possible columns in the working region

                                        // if the columns already have this value from another Region, pass
                                        if(possibleColumns[j]) {
                                                possibles.push_back(vector<bool>(3, true));
                                                continue;
                                        } else {
                                                possibles.push_back(vector<bool>(3, false));
                                        }
                                        
                                        // Possible or not due to the value in another column of main_row
                                        possibles[j][0] = ioGrid.getRegion(3*((main_row+0)%3) + (main_col+1)%3).topRow().isValuePresent(value) || ioGrid.getRegion(3*((main_row+0)%3) + (main_col+2)%3).topRow().isValuePresent(value); 
                                        possibles[j][1] = ioGrid.getRegion(3*((main_row+0)%3) + (main_col+1)%3).middleRow().isValuePresent(value) || ioGrid.getRegion(3*((main_row+0)%3) + (main_col+2)%3).middleRow().isValuePresent(value); 
                                        possibles[j][2] = ioGrid.getRegion(3*((main_row+0)%3) + (main_col+1)%3).bottomRow().isValuePresent(value) || ioGrid.getRegion(3*((main_row+0)%3) + (main_col+2)%3).bottomRow().isValuePresent(value); 
                                        
                                        // get the triplet corresponding to j
                                        if(j == 0) {
                                                fillableTriplet = regions[0].leftColumn();
                                        } else if (j == 1) {
                                                fillableTriplet = regions[0].middleColumn();
                                        } else if (j == 2) {
                                                fillableTriplet = regions[0].rightColumn();
                                        }

                                        // Cannot be place in cells that are not empty
                                        if(!fillableTriplet.getFirst()->isEmpty()) {
                                                possibles[j][0] = true;
                                        }
                                        if(!fillableTriplet.getSecond()->isEmpty()) {
                                                possibles[j][1] = true;
                                        }
                                        if(!fillableTriplet.getThird()->isEmpty()) {
                                                possibles[j][2] = true;
                                        }
                                }

                                // If there is only one possible position where it could be, place it
                                position = findOnlyOneNegative(possibles);
                                if (position.first!=-1) {
                                        if(position.first == 0) {
                                                if(position.second == 0) {
                                                        *(regions[0].leftColumn().getFirst()) = value;
                                                } else if(position.second == 1) {
                                                        *(regions[0].leftColumn().getSecond()) = value;
                                                } else if(position.second == 2) {
                                                        *(regions[0].leftColumn().getThird()) = value;
                                                }
                                        } else if(position.first == 1) {
                                                if(position.second == 0) {
                                                        *(regions[0].middleColumn().getFirst()) = value;
                                                } else if(position.second == 1) {
                                                        *(regions[0].middleColumn().getSecond()) = value;
                                                } else if(position.second == 2) {
                                                        *(regions[0].middleColumn().getThird()) = value;
                                                }
                                        } else if(position.first == 2) {
                                                if(position.second == 0) {
                                                        *(regions[0].rightColumn().getFirst()) = value;
                                                } else if(position.second == 1) {
                                                        *(regions[0].rightColumn().getSecond()) = value;
                                                } else if(position.second == 2) {
                                                        *(regions[0].rightColumn().getThird()) = value;
                                                }
                                        }
                                        ++changed;
                                }
                        }
                } 


                
        }
        return changed;
}

pair<int,int> findOnlyOneNegative(std::vector<std::vector<bool>> possibles) {
        pair<int,int> position(-1,-1);

        int totalNegative = 0;
        for(int i=0; i<3; ++i) {
                for(int j=0; j<3; ++j) {
                        if(possibles[i][j] == false) {
                                totalNegative += 1;
                                position = pair<int,int>(i,j);
                        }
                }
        }

        if(totalNegative == 1) {
                return position;
        }

        return pair<int,int>(-1,-1);
}