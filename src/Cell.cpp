#include <stdexcept>
#include "Cell.hpp"


Cell::Cell(){
    value = 0;
}

Cell::Cell(int x){
    if (x>9 || x<1) {
        throw std::invalid_argument("The value in a Cell must be between 0 and 9.");
    }
    value = x;
}

bool Cell::isEmpty(){
    return value==0;
}

Cell & Cell::operator=(unsigned char iValue) {
    if (iValue>9 || iValue<1) {
        throw std::invalid_argument("The value in a Cell must be between 0 and 9.");
    }
    value = iValue;
}
