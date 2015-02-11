#ifndef CELL_HPP
#define CELL_HPP


class Cell {

public:
    int value;

    Cell();
    Cell(int x);
    bool isEmpty();
    Cell & operator =(unsigned char iValue);
};

#endif
