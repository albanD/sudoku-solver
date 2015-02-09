#include <iostream>
#include <stdexcept>

#include "Cell.hpp"
#include "Region.hpp"

using namespace std;

int check_cells_methods();
int check_region_methods();

int main() {
    int error_happened = 0;

    error_happened += check_cells_methods();
    error_happened += check_region_methods();

    return 0;
}


int check_cells_methods() {

    // Check that the default Cell Constructor works properly
    Cell myCell = Cell(8);
    cout << myCell.value << endl;

    // Check that an exception is raised in case of bad value
    bool exception_raised = false;
    try {
        Cell myCell = Cell(12);
    } catch(domain_error const& e) {
        cout<<"Caught an exception as expected" <<endl;
        exception_raised = true;
    }

    if(not exception_raised) {
        cerr << "No exception was raised"<< endl;
        return 1;
    }
    return 0;

}

int check_region_methods() {
    Region myRegion = Region("123456789");
    return 0;
}
