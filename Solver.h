//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_SOLVER_H
#define PROJECT2_SOLVER_H

#include <string>
using namespace std;

class Solver {
public:
   virtual string solve(string problem) = 0;
   virtual ~Solver() = default;
};

#endif //PROJECT2_SOLVER_H
