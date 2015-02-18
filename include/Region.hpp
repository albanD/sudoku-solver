#include "Cell.hpp"
#include <string>
#include <array>

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
        Region();
        bool isFull() const;
private:
        Cell generate_cell(std::string::iterator iter);

};




#endif
