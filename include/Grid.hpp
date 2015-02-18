#ifndef GRID_HPP
#define GRID_HPP

#include <array>
#include <exception>

#include "Region.hpp"
#include "RegionHolder.hpp"
#include "Cell.hpp"


class Grid {
private:
        std::array<std::array<Region,3>,3> regions;

public:
        Grid(std::array<std::array<Region,3>,3> regions);
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


class InvalidGridException: public std::exception {
public:
        InvalidGridException() throw(){ };
        ~InvalidGridException() throw(){};

        virtual const char* what() const throw() {return "The Grid is invalid";};
};

#endif
