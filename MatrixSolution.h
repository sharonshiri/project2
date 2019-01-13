//
// Created by sharon on 12/01/19.
//

#ifndef PROJECT2_SOLUTION_H
#define PROJECT2_SOLUTION_H

#include "State.h"
#include <list>
#include <string>

using namespace std;

class MatrixSolution {
    list<State<pair<int,int>>> myList;
    double cost;
    string getCurrDirection(State<pair<int,int>> first, State<pair<int,int>> second);
public:

    MatrixSolution(list<State<pair<int,int>>>);
    double getCostOfTrace();
    string getPairString();
    string getDirectionString();
    bool operator<(MatrixSolution other);
};


#endif //PROJECT2_SOLUTION_H
