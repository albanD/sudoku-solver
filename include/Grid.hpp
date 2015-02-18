#ifndef GRID
#define GRID
#include "Region.hpp"
#include "RegionHolder.hpp"
#include "Cell.hpp"
#include <array>
#include <exception>

using namespace std;


class Grid {
private:
        array<array<Region,3>,3> regions;

public:
        Grid(array<array<Region,3>,3> regions);
        bool isFull();
        RegionHolder NO();
        RegionHolder N();
        RegionHolder NE();
        RegionHolder O();
        RegionHolder C();
        RegionHolder E();
        RegionHolder SO();
        RegionHolder S();
        RegionHolder SE();

        RegionHolder getRegion(int reg_index);

        bool accept(class IVisitor& v);
        void show();
        Cell& getCell(int row, int col);

        bool isConsistent();

        Grid getCopy();

        void solve();
};


class InvalidGridException: public exception {
public:
        InvalidGridException() throw(){ };
        ~InvalidGridException() throw(){};

        virtual const char* what() const throw() {return "The Grid is invalid";};
};

#endif
