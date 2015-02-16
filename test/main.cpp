#include <iostream>
#include <stdexcept>

#include "Cell.hpp"
#include "Region.hpp"
#include "ColumnHolder.hpp"
#include "RowHolder.hpp"
#include "RegionHolder.hpp"
#include "LastCellFinder.hpp"
#include "Grid.hpp"
#include "OnlyOneChoiceInColumnVisitor.hpp"
#include "OnlyOneChoiceInRegionVisitor.hpp"
#include "OnlyOneChoiceInRowVisitor.hpp"
#include "OnlySquareVisitor.hpp"
#include "TwoOutOfThreeColumnVisitor.hpp"
#include "TwoOutOfThreeRowVisitor.hpp"

using namespace std;

int check_cells_methods();
int check_region_methods();
int check_last_cell_finder();
int check_full_sudoku();
int check_intermediary();
int check_two_out_of_three();
int check_end_part_3();

int main() {
    int error_happened = 0;

    cout<<endl<<"Starting to check Cell methods:"<<endl;
    error_happened += check_cells_methods();

    cout<<endl<<"Starting to check Region methods:"<<endl;
    error_happened += check_region_methods();

    cout<<endl<<"Starting to check LastCellFinder methods:"<<endl;
    error_happened += check_last_cell_finder();

    cout<<endl<<"Starting to check Full Sudokus methods:"<<endl;
    error_happened += check_full_sudoku();

    cout<<endl<<"Starting to check Intermediary resolution methods:"<<endl;
    error_happened += check_intermediary();

    cout<<endl<<"Starting to check two out of three resolution methods:"<<endl;
    error_happened += check_two_out_of_three();

    cout<<endl<<"Starting to check all the simple methods on the given test grid:"<<endl;
    error_happened += check_end_part_3();

    return error_happened;
}

int check_last_cell_finder() {
    int errors = 0;

    Region myRegion_true = Region("12345678-");
    Region myRegion_false = Region("1234567--");

    RegionHolder true_holder = RegionHolder(myRegion_true);
    RegionHolder false_holder = RegionHolder(myRegion_false);

    LastCellFinder lf_true(true_holder.topRow(),
                           true_holder.middleRow(),
                           true_holder.bottomRow());
    LastCellFinder lf_false(false_holder.topRow(),
                            false_holder.middleRow(),
                            false_holder.bottomRow());

    bool true_res = lf_true.fill();
    cout<<"Filling out true_holder resulted in "<<true_res<<" should be 1"<<endl;
    cout<<"Value in true that should have been filled out: "<<myRegion_true.SE.value<<" should have been 9"<<endl;
    errors += (true_res!=true);
    errors += (myRegion_true.SE.value!=9);

    bool false_res = lf_false.fill();
    cout<<"Filling out false_holder resulted in "<<false_res<<" should be 0"<<endl;
    cout<<"Empty value is still empty "<<myRegion_false.SE.isEmpty()<<" should be 1"<<endl;
    errors += (false_res!=false);
    errors += (myRegion_false.SE.isEmpty()!=true);

    return errors;
}

int check_full_sudoku(){
    int errors = 0;

    //We are missing a 2 at the bottom right
    //Can be reused to initialize several grid.
    array<array<Region,3>,3> content= {
        Region("295431876"), Region("743865192"), Region("861927543"),
        Region("387612549"), Region("459387216"), Region("216495738"),
        Region("763928154"), Region("534671938"), Region("18935467-")
    };

    Grid myGrid_row(content);
    OnlyOneChoiceInRowVisitor row_visitor;
    myGrid_row.accept(&row_visitor);
    cout<<"Row - Previously empty Cell is now: "<<myGrid_row.SE().getSE()->value<<" should be 2"<<endl;
    errors += (myGrid_row.SE().getSE()->value!=2);


    Grid myGrid_col(content);
    OnlyOneChoiceInColumnVisitor col_visitor;
    myGrid_col.accept(&col_visitor);
    cout<<"Col - Previously empty Cell is now: "<<myGrid_col.SE().getSE()->value<<" should be 2"<<endl;
    errors += (myGrid_col.SE().getSE()->value!=2);

    Grid myGrid_reg(content);
    OnlyOneChoiceInRegionVisitor reg_visitor;
    myGrid_reg.accept(&reg_visitor);
    cout<<"Reg - Previously empty Cell is now: "<<myGrid_reg.SE().getSE()->value<<" should be 2"<<endl;
    errors += (myGrid_reg.SE().getSE()->value!=2);


    return errors;

}

int check_intermediary(){
    int errors = 0;

    OnlySquareVisitor square_visitor;

    //We are missing a 2 at the bottom right and a 1 at the bottom left
    array<array<Region,3>,3> content_row= {
        Region("295431876"), Region("743865192"), Region("861927543"),
        Region("387612549"), Region("459387216"), Region("216495738"),
        Region("763928-54"), Region("534671938"), Region("18935467-")
    };
    Grid myGrid_square_row(content_row);
    myGrid_square_row.accept(&square_visitor);
    cout<<"OneSquareRow - Previously empty bottom right Cell is now: "<<myGrid_square_row.SE().getSE()->value<<" should be 2"<<endl;
    cout<<"OneSquareRow - Previously empty bottom left Cell is now: "<<myGrid_square_row.SO().getSO()->value<<" should be 1"<<endl;
    errors += (myGrid_square_row.SE().getSE()->value!=2);
    errors += (myGrid_square_row.SO().getSO()->value!=1);

    //We are missing a 2 at the bottom right and a 8 at the bottom right of E
    array<array<Region,3>,3> content_col= {
        Region("295431876"), Region("743865192"), Region("861927543"),
        Region("387612549"), Region("459387216"), Region("21649573-"),
        Region("763928154"), Region("534671938"), Region("18935467-")
    };
    Grid myGrid_square_col(content_col);
    myGrid_square_col.accept(&square_visitor);
    cout<<"OneSquareCol - Previously empty bottom right Cell is now: "<<myGrid_square_col.SE().getSE()->value<<" should be 2"<<endl;
    cout<<"OneSquareCol - Previously empty mid-bottom right Cell is now: "<<myGrid_square_col.E().getSE()->value<<" should be 8"<<endl;
    errors += (myGrid_square_col.SE().getSE()->value!=2);
    errors += (myGrid_square_col.E().getSE()->value!=8);


    return errors;


}

int check_cells_methods() {
    int errors = 0;

    // Check that the default Cell Constructor works properly
    Cell myCell1 = Cell(8);
    cout << "myCell1 value is "<< myCell1.value << " should be 8"<<endl;
    errors += myCell1.value!=8;

    // Check that an exception is raised in case of bad value
    bool exception_raised = false;
    Cell myCell;
    try {
        myCell = Cell(12);
    } catch(invalid_argument const& e) {
        cout<<"Caught a cell exception as expected" <<endl;
        exception_raised = true;
    }
    // Check that the equal sign raises the same exception
    try {
        myCell = Cell(0);
        myCell.value = 12;
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

    cout << "My triplet is full: "<<triplet.isFull()<<", should be 1"<<endl;

    RowHolder row(&myCell1, &myCell2, &myCell3);
    cout << "Value of the left cell of the row is: "<<row.G()->value<<" should be 8"<<endl;
    errors += (row.G()->value!=8);


    ColumnHolder col(&myCell1, &myCell2, &myCell3);
    cout << "Value of the top cell of the col is: "<<col.T()->value<<" should be 8"<<endl;
    errors += (col.T()->value!=8);


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
        myRegion.isFull(); // Use the myRegion variable to prevent compilation warning
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

    RegionHolder rh = RegionHolder(myRegion2);
    cout<< "Topmost-leftmost of the region holded is " << rh.getNO()->value << " should be 1"<<endl;
    errors += (rh.getNO()->value!=1);


    return errors;


}

int check_two_out_of_three() {
    int errors = 0;

    TwoOutOfThreeRowVisitor twoOutOfThreeRowVisitor;
    TwoOutOfThreeColumnVisitor twoOutOfThreeColumnVisitor;

    //The array given in the subject to test the row
    array<array<Region,3>,3> content_row= {
        Region("--9634125"), Region("51----639"), Region("-6259-7-4"),
        Region("---------"), Region("--7---32-"), Region("---------"),
        Region("---------"), Region("173------"), Region("---------")
    };
    Grid myGrid(content_row);

    bool res = myGrid.accept(&twoOutOfThreeRowVisitor);
    
    cout<<"Two out of three row visitor shoud have filled something (return 1), it returned: "<<res<<endl;
    errors += (res!=1);
    cout<<"Top-left of the top-right region should be filled with 3, it is: "<<myGrid.NE().getNO()->value<<endl;
    errors += (myGrid.NE().getNO()->value!=3);

    myGrid = Grid(content_row);
    res = myGrid.accept(&twoOutOfThreeColumnVisitor);
    
    cout<<"Two out of three column visitor shoud have filled something (return 1), it returned: "<<res<<endl;
    errors += (res!=1);
    cout<<"Middle-left of the middle-top region should be filled with 7, it is: "<<myGrid.N().getO()->value<<endl;
    errors += (myGrid.N().getO()->value!=7);

    return errors;
}

int check_end_part_3() {
    int errors = 0;

    OnlyOneChoiceInRowVisitor onlyOneChoiceInRowVisitor;
    OnlyOneChoiceInColumnVisitor onlyOneChoiceInColumnVisitor;
    OnlyOneChoiceInRegionVisitor onlyOneChoiceInRegionVisitor;
    OnlySquareVisitor onlySquareVisitor;
    TwoOutOfThreeRowVisitor twoOutOfThreeRowVisitor;
    TwoOutOfThreeColumnVisitor twoOutOfThreeColumnVisitor;

    //The array given in the subject to test the simple visitors
    array<array<Region,3>,3> content_row= {
        Region("-----6--9"), Region("--23----1"), Region("6-3--1-52"),
        Region("782----5-"), Region("---------"), Region("-9----726"),
        Region("24-8--6-5"), Region("1----48--"), Region("8--5-----")
    };
    Grid myGrid(content_row);

    bool somethingDone = true;
    while (somethingDone) {
        somethingDone = false;
        somethingDone |= myGrid.accept(&onlyOneChoiceInRowVisitor);
        somethingDone |= myGrid.accept(&onlyOneChoiceInColumnVisitor);
        somethingDone |= myGrid.accept(&onlyOneChoiceInRegionVisitor);
        somethingDone |= myGrid.accept(&onlySquareVisitor);
        somethingDone |= myGrid.accept(&twoOutOfThreeRowVisitor);
        somethingDone |= myGrid.accept(&twoOutOfThreeColumnVisitor);
    }

    cout<<"Simple method should have filled the grid. Grid.isFull="<<myGrid.isFull()<<" (1 expected)"<<endl;
    errors+=(myGrid.isFull()!=true);

    return errors;
}