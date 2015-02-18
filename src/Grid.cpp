#include "Region.hpp"
#include "ColumnHolder.hpp"
#include "RegionHolder.hpp"
#include "Grid.hpp"
#include "IVisitor.hpp"
#include <array>
#include <iostream>

using namespace std;

Grid::Grid(array<array<Region,3>,3> regions) {
        this->regions = regions;
}

bool Grid::isFull(){
        for(array<array<Region,3>,3>::iterator liter=regions.begin(),lend=regions.end();liter!=lend;++liter){
                for(array<Region,3>::iterator citer=liter->begin(),cend=liter->end(); citer!=cend; ++citer){
                        if (not citer->isFull()){
                                return false;
                        }
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
                        cout<<endl;
                }
                for(int j=0;j<9;++j){
                        if (j%3==0) {
                                cout<<"  ";
                        }
                        int value = getCell(i,j).value;
                        cout<< value<<" ";
                }
                cout<<endl;
        }
}

bool Grid::accept(IVisitor& v){
        return v.Visit(*this);
};
