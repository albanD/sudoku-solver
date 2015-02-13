#include "LastCellFinder.hpp"

#include "Holder.hpp"
#include <array>

using namespace std;

LastCellFinder::LastCellFinder(TripleHolder h1, TripleHolder h2, TripleHolder h3){
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
                if (holders[i].getFirst()->isEmpty()){
                        empty_holder = i;
                        empty_pos = 1;
                        nb_empty++;
                } else{
                        int pos =(int) *(holders[i].getFirst()) -1;
                        index[pos] = true;
                }


                if (holders[i].getSecond()->isEmpty()){
                        empty_holder = i;
                        empty_pos = 2;
                        nb_empty++;
                } else{
                        int pos =(int) *(holders[i].getSecond()) -1;
                        index[pos] = true;
                }


                if (holders[i].getThird()->isEmpty()){
                        empty_holder = i;
                        empty_pos = 3;
                        nb_empty++;
                } else{

                        int pos = (int) *(holders[i].getThird()) -1;
                        index[pos] = true;
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

        if(empty_pos==1){*(holders[empty_holder].getFirst())=missing_value;}
        if(empty_pos==2){*(holders[empty_holder].getSecond())=missing_value;}
        if(empty_pos==3){*(holders[empty_holder].getThird())=missing_value;}

        return true;

}
