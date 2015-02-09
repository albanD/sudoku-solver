#include <stdexcept>
#include <iostream>
#include "Region.hpp"

using namespace std;

Region::Region(string init_string) {
        for(string::iterator it= init_string.begin(); it !=init_string.end(); ++it) {
                cout << *it << endl;
        }
}
