#include "RowHolder.hpp"
#include "Cell.hpp"


Cell &RowHolder::G(){return getFirst();}
Cell &RowHolder::C(){return getSecond();}
Cell &RowHolder::D(){return getThird();}
