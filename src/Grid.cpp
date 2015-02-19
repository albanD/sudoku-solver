#include <array>
#include <iostream>
#include <unordered_set>

#include "Region.hpp"
#include "RegionHolder.hpp"
#include "TripleTripleHolder.hpp"
#include "Grid.hpp"
#include "IVisitor.hpp"
#include "ValueEliminator.hpp"
#include "OnlyOneChoiceInColumnVisitor.hpp"
#include "OnlyOneChoiceInRegionVisitor.hpp"
#include "OnlyOneChoiceInRowVisitor.hpp"
#include "OnlySquareVisitor.hpp"
#include "TwoOutOfThreeColumnVisitor.hpp"
#include "TwoOutOfThreeRowVisitor.hpp"
#include "FillAnySureVisitor.hpp"

Grid::Grid(std::array<std::array<Region,3>,3> regions) {
        this->regions = regions;
}

bool Grid::isFull(){
        for(int i=0; i<9; ++i) {
                if(!getRegion(i).isFull()) {
                        return false;
                }
        }
        return true;
}

RegionHolder Grid::NO(){return RegionHolder(regions[0][0]);}
RegionHolder Grid::N(){return RegionHolder(regions[0][1]);}
RegionHolder Grid::NE(){return RegionHolder(regions[0][2]);}
RegionHolder Grid::O(){return RegionHolder(regions[1][0]);}
RegionHolder Grid::C(){return RegionHolder(regions[1][1]);}
RegionHolder Grid::E(){return RegionHolder(regions[1][2]);}
RegionHolder Grid::SO(){return RegionHolder(regions[2][0]);}
RegionHolder Grid::S(){return RegionHolder(regions[2][1]);}
RegionHolder Grid::SE(){return RegionHolder(regions[2][2]);}

RegionHolder Grid::getRegion(int reg_index){
        int main_row = reg_index / 3;
        int main_col = reg_index - (3*main_row);
        return RegionHolder(regions[main_row][main_col]);
}

Cell& Grid::getCell(int row, int col){
        int main_row = row /3;
        int main_col = col /3;
        int sub_row = row - 3* main_row;
        int sub_col = col - 3* main_col;
        RegionHolder rh = RegionHolder(regions[main_row][main_col]);
        return rh.getCell(3*sub_row + sub_col);
}

void Grid::show(){
        for(int i=0;i<9;++i){
                if (i%3==0) {
                        std::cout<<std::endl;
                }
                for(int j=0;j<9;++j){
                        if (j%3==0) {
                                std::cout<<"  ";
                        }
                        int value = getCell(i,j).value;
                        std::cout<< value<<" ";
                }
                std::cout<<std::endl;
        }
}

bool Grid::accept(IVisitor& v){
        return v.Visit(*this);
};

bool Grid::isConsistent() {
        int i,j;

        for(i=0; i<9; ++i) {
                // test each region
                if(!(TripleTripleHolder(getRegion(i)).isConsistent())) {
                        return false;
                }
                //test each column
                if(!(TripleTripleHolder(getRegion(i/3).getColumn(i%3), getRegion(i/3+3).getColumn(i%3), getRegion(i/3+6).getColumn(i%3)).isConsistent())) {
                        return false;
                }
                // test each row
                if(!(TripleTripleHolder(getRegion((i/3)*3).getRow(i%3), getRegion((i/3)*3+1).getRow(i%3), getRegion((i/3)*3+2).getRow(i%3)).isConsistent())) {
                        return false;
                }
        }

        return true;
}

Grid Grid::getCopy() {
        std::array<std::array<Region,3>,3> newRegions = std::array<std::array<Region,3>,3>();

        for(int i=0; i<3; ++i) {
                for(int j=0; j<3; ++j) {
                        RegionHolder newrh(newRegions[i][j]);
                        RegionHolder oldrh = getRegion(i*3 + j);
                        for(int k=0; k<9; ++k) {
                                newrh.getCell(k) = oldrh.getCell(k);
                        }
                }
        }

        return Grid(newRegions);
}

void Grid::solve() {
        // declare visitors
        std::vector<IVisitor*> visitors = std::vector<IVisitor*>();
        OnlyOneChoiceInRowVisitor onlyOneChoiceInRowVisitor = OnlyOneChoiceInRowVisitor();
        visitors.push_back(&onlyOneChoiceInRowVisitor);
        OnlyOneChoiceInColumnVisitor onlyOneChoiceInColumnVisitor = OnlyOneChoiceInColumnVisitor();
        visitors.push_back(&onlyOneChoiceInColumnVisitor);
        OnlyOneChoiceInRegionVisitor onlyOneChoiceInRegionVisitor = OnlyOneChoiceInRegionVisitor();
        visitors.push_back(&onlyOneChoiceInRegionVisitor);
        OnlySquareVisitor onlySquareVisitor = OnlySquareVisitor();
        visitors.push_back(&onlySquareVisitor);
        TwoOutOfThreeRowVisitor twoOutOfThreeRowVisitor = TwoOutOfThreeRowVisitor();
        visitors.push_back(&twoOutOfThreeRowVisitor);
        TwoOutOfThreeColumnVisitor twoOutOfThreeColumnVisitor = TwoOutOfThreeColumnVisitor();
        visitors.push_back(&twoOutOfThreeColumnVisitor);
        FillAnySureVisitor fillAnySureVisitor = FillAnySureVisitor();
        visitors.push_back(&fillAnySureVisitor);

        int nbrVisitors = visitors.size();

        int i,j;
        int reg_row,reg_col,cellInd;
        bool found,keepDoingSimple;
        ValueEliminator ve;
        std::unordered_set<int> valuesToTest;

        keepDoingSimple = true;
        // try to fill the grid with simple methods
        while(keepDoingSimple) {
                keepDoingSimple = false;
                for(i=0; i<nbrVisitors; ++i) {
                        keepDoingSimple |= accept(*(visitors[i]));
                        // if we finished, return
                        if(isFull()) {
                                return;
                        }
                        // if we lost consistency, raise an error
                        if(!isConsistent()) {
                                throw InvalidGridException();
                        }
                }
        }

        // unable to keep filling the grid, take a guess
        found = false;
        for(i=2; i<10; ++i) {
                // for any possible number of possible values for a cell
                for(reg_row=0; reg_row<3; ++reg_row) {
                        // for row of region
                        for(reg_col=0; reg_col<3; ++reg_col) {
                                // for col of region
                                // if region is not full
                                if(getRegion(reg_row*3+reg_col).isFull()) {continue;}

                                for(cellInd=0; cellInd<9; ++cellInd) {
                                        //for each empty Cell of the region
                                        if(getRegion(reg_row*3+reg_col).getCell(cellInd).value != 0) {continue;}

                                        // find the number of possible values
                                        ve = ValueEliminator();
                                        // flag values present in the region
                                        TripleTripleHolder(getRegion(reg_row*3+reg_col)).flagValues(ve);
                                        // flag values present in the line
                                        TripleTripleHolder(getRegion(reg_row*3+reg_col).getRow(cellInd/3), getRegion(reg_row*3+(reg_col+1)%3).getRow(cellInd/3), getRegion(reg_row*3+(reg_col+2)%3).getRow(cellInd/3)).flagValues(ve);
                                        // flag values present in the column
                                        TripleTripleHolder(getRegion(reg_row*3+reg_col).getColumn(cellInd%3), getRegion(((reg_row+1)%3)*3+reg_col).getColumn(cellInd%3), getRegion(((reg_row+2)%3)*3+reg_col).getColumn(cellInd%3)).flagValues(ve);
                                        
                                        if(ve.availableValues()==i) {
                                                found = true;
                                                break;
                                        }
                                }
                                if(found) {break;}
                        }
                        if(found) {break;}
                }
                if(found) {break;}
        }

        // Check if the grid is correct
        if(i==10) {
                throw InvalidGridException();
        }

        valuesToTest = ve.availableValue();

        // try all possible values one by one
        for(std::unordered_set<int>::iterator it = valuesToTest.begin(), end = valuesToTest.end(); it!=end; ++it) {
                // create a new grid with the guess
                Grid tempGrid = getCopy();
                tempGrid.getRegion(reg_row*3+reg_col).getCell(cellInd) = *it;
                
                try {
                        // try to solve the grid with the guess
                        tempGrid.solve();
                        *this = tempGrid;
                        break;
                } catch(InvalidGridException const &e) {}
        }

        if(!isFull() || !isConsistent()) {
                throw InvalidGridException();
        }
}