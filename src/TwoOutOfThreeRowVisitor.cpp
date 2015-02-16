#include "TwoOutOfThreeRowVisitor.hpp"
#include "Grid.hpp"
#include "RegionHolder.hpp"
#include <vector>
#include <iostream>
using namespace std;

TwoOutOfThreeRowVisitor::TwoOutOfThreeRowVisitor(){}

// For local use only
pair<int,int> findOnlyOneNegativeInRows(std::vector<std::vector<bool>> possibles);

bool TwoOutOfThreeRowVisitor::Visit(Grid &ioGrid) const{
        bool changed = false;
        std::vector<RegionHolder> regions;
        std::vector<std::vector<bool>> possibles;
        std::vector<bool> possibleColumns;
        pair<int,int> position;
        int line;
        std::vector<bool>::iterator it;
        TripleHolder fillableTriplet;

        for(int main_row=0; main_row<3;++main_row) {
                // horizontal

                for(int i=0; i<3; ++i) {
                        // work with the ith region in this line
                        regions = std::vector<RegionHolder>();
                        regions.push_back(ioGrid.getRegion(3*main_row + (i+0)%3));
                        regions.push_back(ioGrid.getRegion(3*main_row + (i+1)%3));
                        regions.push_back(ioGrid.getRegion(3*main_row + (i+2)%3));
                        
                        for(int value = 1; value<=9; ++value) {
                                // test for all different values
                                //
                                if(regions[0].isValuePresent(value)){continue;}

                                // value is not present in the ith region
                                // find the line where it should be
                                
                                possibleColumns = vector<bool>(3, false);
                                position = regions[1].valuePosition(value);
                                if (position.first != -1) {
                                        possibleColumns[position.first] = true;
                                }
                                position = regions[2].valuePosition(value);
                                if (position.first != -1) {
                                        possibleColumns[position.first] = true;
                                }

                                // find the column where it should be
                                possibles = std::vector<std::vector<bool>>();
                                for(int j=0; j<3; ++j) {
                                
                                        // if the row already have this value from another Region, pass
                                        if(possibleColumns[j]) {
                                                possibles.push_back(vector<bool>(3, true));
                                                continue;
                                        } else {
                                                possibles.push_back(vector<bool>(3, false));
                                        }

                                        possibles[j][0] = ioGrid.getRegion(3*((main_row+1)%3) + (i+0)%3).leftColumn().isValuePresent(value) || ioGrid.getRegion(3*((main_row+2)%3) + (i+0)%3).leftColumn().isValuePresent(value); 
                                        possibles[j][1] = ioGrid.getRegion(3*((main_row+1)%3) + (i+0)%3).middleColumn().isValuePresent(value) || ioGrid.getRegion(3*((main_row+2)%3) + (i+0)%3).middleColumn().isValuePresent(value); 
                                        possibles[j][2] = ioGrid.getRegion(3*((main_row+1)%3) + (i+0)%3).rightColumn().isValuePresent(value) || ioGrid.getRegion(3*((main_row+2)%3) + (i+0)%3).rightColumn().isValuePresent(value); 
                                        
                                        // Cannot be place in cells that are not empty
                                        if(j == 0) {
                                                fillableTriplet = regions[0].topRow();
                                        } else if (j == 1) {
                                                fillableTriplet = regions[0].middleRow();
                                        } else if (j == 2) {
                                                fillableTriplet = regions[0].bottomRow();
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
                                position = findOnlyOneNegativeInRows(possibles);
                                if (position.first!=-1) {
                                        if(position.first == 0) {
                                                if(position.second == 0) {
                                                        *(regions[0].topRow().getFirst()) = value;
                                                } else if(position.second == 1) {
                                                        *(regions[0].topRow().getSecond()) = value;
                                                } else if(position.second == 2) {
                                                        *(regions[0].topRow().getThird()) = value;
                                                }
                                        } else if(position.first == 1) {
                                                if(position.second == 0) {
                                                        *(regions[0].middleRow().getFirst()) = value;
                                                } else if(position.second == 1) {
                                                        *(regions[0].middleRow().getSecond()) = value;
                                                } else if(position.second == 2) {
                                                        *(regions[0].middleRow().getThird()) = value;
                                                }
                                        } else if(position.first == 2) {
                                                if(position.second == 0) {
                                                        *(regions[0].bottomRow().getFirst()) = value;
                                                } else if(position.second == 1) {
                                                        *(regions[0].bottomRow().getSecond()) = value;
                                                } else if(position.second == 2) {
                                                        *(regions[0].bottomRow().getThird()) = value;
                                                }
                                        }
                                        ++changed;
                                }
                        }
                } 
              
        }
        return changed;
}

pair<int,int> findOnlyOneNegativeInRows(std::vector<std::vector<bool>> possibles) {
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