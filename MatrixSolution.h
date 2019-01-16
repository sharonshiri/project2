//
// Created by sharon on 12/01/19.
//

#ifndef PROJECT2_SOLUTION_H
#define PROJECT2_SOLUTION_H

#include "State.h"
#include "Searcher.h"
#include <list>
#include <string>

using namespace std;

class MatrixSolution {
    string getCurrDirection(State<pair<int,int>>* first, State<pair<int,int>>* second);
public:

    double calcCost(list<State<pair<int,int>>*> list);
    string getPairString(list<State<pair<int,int>>*> list,Searcher<pair<int,int>>* searcher);
    string getDirectionString(list<State<pair<int,int>>*>);
    pair<double,int> getPair(list<State<pair<int,int>>*> list, Searcher<pair<int,int>>* searcher);
};


#endif //PROJECT2_SOLUTION_H
