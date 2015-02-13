#ifndef VALUEELIMINATOR
#define VALUEELIMINATOR
#include <array>
#include <unordered_set>
#include <exception>

using namespace std;

class ValueEliminator{
private:
        array<bool,9> seen;
public:
        ValueEliminator();
        void flag(unsigned char iValue);
        int availableValues() const;
        unordered_set<int> availableValue() const;
};

class NoAvailableValueException : public exception{
public:
        NoAvailableValueException() throw(){ };
        ~NoAvailableValueException() throw();

        virtual const char* what() const throw() {return "No Available value";};

};

#endif
