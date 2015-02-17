#ifndef CELL_HPP
#define CELL_HPP


class Cell {

public:
    int value;

    Cell();
    Cell(int x);
    bool isEmpty() const;
    Cell & operator =(unsigned char iValue);
    operator unsigned char () const;
    operator long unsigned int () const;
    bool operator ==(unsigned char iValue);
};

#endif
