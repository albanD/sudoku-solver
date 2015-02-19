#include <stdexcept>
#include <string.h>

#include "Region.hpp"

Region::Region(){
        Region("---------");
}

Region::Region(std::string init_string) {
        if (init_string.length() != 9) {
                throw std::invalid_argument("This initialization string is not of the right size.");
        }

        std::string::iterator iter = init_string.begin();
        
        NO = generate_cell(*iter); ++iter;
        N = generate_cell(*iter); ++iter;
        NE = generate_cell(*iter); ++iter;
        O = generate_cell(*iter); ++iter;
        C = generate_cell(*iter); ++iter;
        E = generate_cell(*iter); ++iter;
        SO = generate_cell(*iter); ++iter;
        S = generate_cell(*iter); ++iter;
        SE = generate_cell(*iter); ++iter;

}

Cell Region::generate_cell(char s_value) {
        Cell new_cell;
        if(s_value == '-') {
                new_cell = Cell();
        } else { // cell is going to throw an invalid_argument exception for every value we don't want.
                int value = s_value-'0';
                new_cell = Cell(value);
        }
        return new_cell;
}

bool Region::isFull() const{
        bool has_empty_cases = false;
        has_empty_cases = has_empty_cases || NO.isEmpty() || N.isEmpty() || NE.isEmpty();
        has_empty_cases = has_empty_cases || O.isEmpty() || C.isEmpty() || E.isEmpty();
        has_empty_cases = has_empty_cases || SO.isEmpty() || S.isEmpty()  || SE.isEmpty();

        return not has_empty_cases;
}
