#include <stdexcept>
#include "Cell.hpp"


 Cell::Cell(int x){
    if (x>9 || x<0) {
        throw std::domain_error("The value in a Cell must be between 0 and 9.");
    }
    value = x;
}