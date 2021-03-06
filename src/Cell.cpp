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

bool Cell::isEmpty() const{
    return value==0;
}

Cell & Cell::operator=(unsigned char iValue) {
    if (iValue>9 || iValue<1) {
        throw std::invalid_argument("The value in a Cell must be between 0 and 9.");
    }
    value = iValue;
}

Cell::operator unsigned char() const{
    return  (unsigned char) value;
}

Cell::operator long unsigned int () const{
    return  (long unsigned int) value;
}


bool Cell::operator ==(unsigned char iValue) const{
    return (unsigned char) value == iValue;
}
