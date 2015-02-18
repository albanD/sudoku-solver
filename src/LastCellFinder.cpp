#include "LastCellFinder.hpp"

#include "TripleHolder.hpp"
#include <array>

using namespace std;

LastCellFinder::LastCellFinder(TripleHolder h1, TripleHolder h2, TripleHolder h3){
        holders = std::vector<TripleHolder>();
        holders.push_back(h1);
        holders.push_back(h2);
        holders.push_back(h3);
}

bool LastCellFinder::fill(){
        // Index of the value that we have already filled, stock where we can find them
        array<bool,9> index = {false,false,false,
                               false,false,false,
                               false,false,false};
        int empty_holder;
        int empty_pos;
        int nb_empty = 0;
        for(int i=0;i<3;++i){
                for(int j=0;j<3;++j){
                        if (holders[i].getCell(j).isEmpty()){
                                empty_holder = i;
                                empty_pos = j;
                                nb_empty++;
                        } else{
                                int pos =(int) holders[i].getCell(j) -1;
                                index[pos] = true;
                        }

                }
        }

        int missing_value;
        if(nb_empty!=1){
                //There is several empty cells, can't do anything
                // or there is no cell to fill
                return false;
        } else {
                // We find the missing value.
                // ASSUMPTION: there is only one missing value-> there was no conflict in our holder
                for(missing_value=0; missing_value<9; ++missing_value){
                        if(not index[missing_value]){
                                break;
                        }
                }
                // Bring it from 0-8 to 1-9
                missing_value++;
        }

        holders[empty_holder].getCell(empty_pos)=missing_value;

        return true;

}
