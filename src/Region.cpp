#include <stdexcept>
#include <iostream>
#include <string.h>
#include "Region.hpp"

using namespace std;
Region::Region(){}

Region::Region(string init_string) {
        if (init_string.length() != 9) {
                throw invalid_argument("This initialization string is not of the right size.");
        }

        string::iterator iter = init_string.begin();
        try{
                NO = generate_cell(iter); ++iter;
                N = generate_cell(iter); ++iter;
                NE = generate_cell(iter); ++iter;
                O = generate_cell(iter); ++iter;
                C = generate_cell(iter); ++iter;
                E = generate_cell(iter); ++iter;
                SO = generate_cell(iter); ++iter;
                S = generate_cell(iter); ++iter;
                SE = generate_cell(iter); ++iter;
        } catch (invalid_argument const& e) {
                cerr << "One of the initialization value is not a number or a '-'"<<endl;
                throw;
        }

}

Cell Region::generate_cell(string::iterator iter) {
        char s_value = *iter;
        Cell new_cell;
        if(s_value == '-') {
                new_cell = Cell();
        } else { // stoi is going to throw an invalid_argument exception for every value we don't want.
                int value = stoi(&s_value, nullptr, 10);
                new_cell = Cell(value);
        }
        return new_cell;
}

bool Region::isFull(){
        bool has_empty_cases = false;
        has_empty_cases = has_empty_cases || NO.isEmpty() || N.isEmpty() || NE.isEmpty();
        has_empty_cases = has_empty_cases || O.isEmpty() || C.isEmpty() || E.isEmpty();
        has_empty_cases = has_empty_cases || SO.isEmpty() || S.isEmpty()  || SE.isEmpty();

        return not has_empty_cases;
}

Grid::Grid(array<array<Region,3>,3> regions) {
        this->regions = regions;
}

bool Grid::isFull(){
        for(array<array<Region,3>,3>::iterator liter=regions.begin(),lend=regions.end();liter!=lend;++liter){
                for(array<Region,3>::iterator citer=liter->begin(),cend=liter->end(); citer!=cend; ++citer){
                        if (not citer->isFull()){
                                return false;
                        }
                }
        }
        return true;
}