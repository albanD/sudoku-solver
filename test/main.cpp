#include <iostream>

#include "Cell.hpp"

using namespace std;

int main() {
    Cell myCell = Cell(8);

    cout << myCell.value << endl;

    return 0;
}