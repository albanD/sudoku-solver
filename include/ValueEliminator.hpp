#ifndef VALUEELIMINATOR_HPP
#define VALUEELIMINATOR_HPP

#include <array>
#include <unordered_set>
#include <exception>


class ValueEliminator{
private:
        std::array<bool,9> seen;
public:
        ValueEliminator();
        void flag(unsigned char iValue);
        int availableValues() const;
        std::unordered_set<int> availableValue() const;
};

class NoAvailableValueException : public std::exception{
public:
        NoAvailableValueException() throw(){ };
        ~NoAvailableValueException() throw(){};

        virtual const char* what() const throw() {return "No Available value";};

};

#endif
