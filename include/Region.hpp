#include "Cell.hpp"
#include <string>

#ifndef REGION_HPP
#define REGION_HPP

class Region {
private:
        Cell N;
        Cell S;
        Cell E;
        Cell O;
        Cell NE;
        Cell SE;
        Cell NO;
        Cell SO;
        Cell C;

public:
        Region(std::string init_string);
};


#endif
