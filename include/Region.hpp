#include "Cell.hpp"
#include <string>

#ifndef REGION_HPP
#define REGION_HPP

class Region {
public:
        Cell N;
        Cell S;
        Cell E;
        Cell O;
        Cell NE;
        Cell SE;
        Cell NO;
        Cell SO;
        Cell C;
        Region(std::string init_string);

private:
        Cell generate_cell(std::string::iterator iter);

};



class Grid {
public:
        std::array<std::array<Region,3>,3> regions;

        Grid(std::array<std::array<Region,3>,3> regions);
}

#endif
