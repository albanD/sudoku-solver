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

    return error_happened;
}


int check_cells_methods() {
    int errors = 0;

    // Check that the default Cell Constructor works properly
    Cell myCell = Cell(8);
    cout << "myCell value is "<< myCell.value << " should be 8"<<endl;
    errors += myCell.value!=8;

    // Check that an exception is raised in case of bad value
    bool exception_raised = false;
    try {
        Cell myCell = Cell(12);
    } catch(invalid_argument const& e) {
        cout<<"Caught a cell exception as expected" <<endl;
        exception_raised = true;
    }

    if(not exception_raised) {
        cerr << "No exception was raised for the cells"<< endl;
        errors++;
    }


    // Check that the overloaded affectation operator works
    Cell myCell2 = Cell();
    myCell2 = 3;
    cout << "myCell2 value is "<< myCell2.value << " should be 3"<<endl;
    errors += myCell2.value!=3;

    unsigned char cell_value = (unsigned char) myCell2;
    cout <<"Casting myCell2 gives a char of value: "<<(int) cell_value << " should be 3"<<endl;
    errors += cell_value!=3;

    return errors;

}

int check_region_methods() {

    // Check the happy path
    Region myRegion = Region("123456789");
    cout << "The value of the topmost-leftmost is "<< myRegion.NO.value <<", supposed to be 1." <<endl;

    // Check that an exception triggers
    bool exception_raised = false;
    try {
        Region myRegion = Region("12345-------");
    } catch(invalid_argument const& e) {
        cout << "Caught a Region exception as expected" <<endl;
        exception_raised = true;
    }

    if(not exception_raised) {
        cerr << "No exception was raised for the Region"<<endl;
        return 1;
    }
    return 0;
}
