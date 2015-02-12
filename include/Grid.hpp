#ifndef GRID
#define GRID
#include "Region.hpp"
#include "Holder.hpp"
#include <array>

using namespace std;


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


};

#endif
