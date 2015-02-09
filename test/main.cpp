#include <iostream>
#include <stdexcept>

#include "Cell.hpp"

using namespace std;

int main() {

    // Check that the default Cell Constructor works properly
    Cell myCell = Cell(8);
    cout << myCell.value << endl;

    // Check that an exception is raised in case of bad value
    bool exception_raised = false;
    try {
        Cell myCell = Cell(12);
    } catch(std::domain_error const& e) {
        cout<<"Caught an exception as expected" <<endl;
        exception_raised = true;
    }

    if(not exception_raised) {
        cerr << "No exception was raised"<< endl;
        return 1;
    }


    return 0;
}