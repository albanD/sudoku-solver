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

                                // value is not present in the ith region
                                // find the col where it should be
                                
                                possibleColumns = vector<bool>(3, false);
                                position = regions[1].valuePosition(value);
                                if (position.second != -1) {
                                        possibleColumns[position.second] = true;
                                }
                                position = regions[2].valuePosition(value);
                                if (position.second != -1) {
                                        possibleColumns[position.second] = true;
                                }



                                // find the rows where it should be
                                possibles = std::vector<std::vector<bool>>();
                                for(int j=0; j<3; ++j) {

                                        // if the columns already have this value from another Region, pass
                                        if(possibleColumns[j]) {
                                                possibles.push_back(vector<bool>(3, true));
                                                continue;
                                        } else {
                                                possibles.push_back(vector<bool>(3, false));
                                        }
                                        
                                        // This is the same for all j
                                        possibles[j][0] = ioGrid.getRegion(3*((i+0)%3) + (main_col+1)%3).topRow().isValuePresent(value) || ioGrid.getRegion(3*((i+0)%3) + (main_col+2)%3).topRow().isValuePresent(value); 
                                        possibles[j][1] = ioGrid.getRegion(3*((i+0)%3) + (main_col+1)%3).middleRow().isValuePresent(value) || ioGrid.getRegion(3*((i+0)%3) + (main_col+2)%3).middleRow().isValuePresent(value); 
                                        possibles[j][2] = ioGrid.getRegion(3*((i+0)%3) + (main_col+1)%3).bottomRow().isValuePresent(value) || ioGrid.getRegion(3*((i+0)%3) + (main_col+2)%3).bottomRow().isValuePresent(value); 
                                        
                                        // Cannot be place in cells that are not empty
                                        if(j == 0) {
                                                fillableTriplet = regions[0].leftColumn();
                                        } else if (j == 1) {
                                                fillableTriplet = regions[0].middleColumn();
                                        } else if (j == 2) {
                                                fillableTriplet = regions[0].rightColumn();
                                        }

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

                                // If there is only one possible position where it could be place it
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