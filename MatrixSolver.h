//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_MATRIXSOLVER_H
#define PROJECT2_MATRIXSOLVER_H

#include <utility>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Solver.h"
#include "MatrixSearchable.h"
#include "MatrixSolution.h"
#include "State.h"

#include "DFS.h"
#include "BestFirstSearch.h"
#include "BFS.h"
//#include "AStar.h"

class MatrixSolver : public Solver {
    int rowNumber,colNumber;
    vector<vector<State<pair<int, int>>>> myMatrix;
    void createMatrix(string &stringMatrix);
    vector<State<pair<int, int>>> parseOneRow(string, int row);
    string getParam(string &message);
    string parseStartState(string &myString);
    string parseFinalState(string &myString);
    State<pair<int, int>> getStateFromMatrix(string);
    void deleteSpaces(string &line);
    string chooseBestAlg(list<list<State<pair<int,int>>*>> myList);
    string findShortestWay(State<pair<int, int>>,State<pair<int, int>>);
public:
    string solve(string stringMatrix);
};


#endif //PROJECT2_MATRIXSOLVER_H
