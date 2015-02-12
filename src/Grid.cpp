#include "Region.hpp"
#include "Holder.hpp"
#include "Grid.hpp"

#include <array>


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
