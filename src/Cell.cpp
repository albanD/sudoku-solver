#include <stdexcept>
#include "Cell.hpp"


Cell::Cell(){
}

Cell::Cell(int x){
    if (x>9 || x<1) {
        throw std::invalid_argument("The value in a Cell must be between 0 and 9.");
    }
    value = x;
}
