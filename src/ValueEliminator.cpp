#include "ValueEliminator.hpp"

ValueEliminator::ValueEliminator(){
        seen = {false, false, false,
                false, false, false,
                false, false, false};
}

void ValueEliminator::flag(unsigned char iValue){
        seen[iValue] = true;
}

int ValueEliminator::availableValues() const{
        int count = 0;
        for(array<bool,0>::const_iterator it= seen.begin(), end=seen.end();it!=end;++it){
                if(not *it){
                        count++;
                }
        }
        return count;
}

unordered_set<int> ValueEliminator::availableValue() const{
        bool at_least_one_free = false;
        unordered_set<int> availables;
        for(int i=0;i<seen.size();++i){
                if(not seen[i]){
                        availables.insert(i+1);
                        at_least_one_free = true;
                }
        }
        if(at_least_one_free){
                return availables;
        } else{
                throw NoAvailableValueException();
        }

}
