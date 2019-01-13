//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_STRINGREVERSE_H
#define PROJECT2_STRINGREVERSE_H

#include "Solver.h"
#include <string>
#include <algorithm>

class StringReverse : public Solver{
public:
    string solve(string myString) {
        reverse(myString.begin(), myString.end());
        return myString;
    }
};


#endif //PROJECT2_STRINGREVERSE_H
