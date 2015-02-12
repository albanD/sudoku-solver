#include <iostream>
#include <stdexcept>

#include "Cell.hpp"
#include "Region.hpp"
#include "Holder.hpp"

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
    Cell myCell1 = Cell(8);
    cout << "myCell1 value is "<< myCell1.value << " should be 8"<<endl;
    errors += myCell1.value!=8;

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

    // Check that the overloaded cast works
    unsigned char cell_value = (unsigned char) myCell2;
    cout <<"Casting myCell2 gives a char of value: "<<(int) cell_value << " should be 3"<<endl;
    errors += cell_value!=3;

    // Check that the overloaded Comparison operator works
    bool true_eq = (myCell2==(unsigned char)3);
    bool false_eq = (myCell2==(unsigned char)4);
    cout << "myCell2==3 returns "<< true_eq << " should be 1"<<endl;
    cout << "myCell2==4 returns "<< false_eq << " should be 0"<<endl;
    errors += (true_eq!=true);
    errors += (false_eq!=false);


    Cell myCell3 = Cell(2);

    TripleHolder triplet(&myCell1, &myCell2, &myCell3);
    cout << "Value of the first cell of the triplet is: "<<triplet.getFirst()->value<<" should be 8"<<endl;
    errors += (triplet.getFirst()->value!=8);


    RowHolder row(&myCell1, &myCell2, &myCell3);
    cout << "Value of the left cell of the row is: "<<row.G()->value<<" should be 8"<<endl;
    errors += (row.G()->value!=8);


    return errors;

}

int check_region_methods() {

    int errors = 0;

    // Check the happy path
    Region myRegion = Region("123456789");
    cout << "The value of the topmost-leftmost is "<< myRegion.NO.value <<", supposed to be 1." <<endl;
    if(myRegion.NO.value!=1){
        errors++;
    }

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
        errors++;
    }

    Region myRegion2 = Region("12345678-");
    cout<< "myRegion is Full: "<< myRegion.isFull() <<" should be 1"<<endl;
    cout<< "myRegion2 is Full: "<< myRegion2.isFull() << " should be 0"<<endl;
    errors += (myRegion.isFull()!=true);
    errors += (myRegion2.isFull()!=false);


    return errors;


}
