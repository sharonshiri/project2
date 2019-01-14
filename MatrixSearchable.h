//
// Created by sharon on 12/01/19.
//

#ifndef PROJECT2_MATRIXSEARCHABLE_H
#define PROJECT2_MATRIXSEARCHABLE_H

#include "Searchable.h"
#include <vector>

template <class T>
class MatrixSearchable : public Searchable<pair<int,int>> {
    State<pair<int,int>> myStart;
    State<pair<int,int>> myFinal;
    vector<vector<State<pair<int,int>>>> myMatrix;
    int myRow,myCol;
public:
    void initializeMatrix() {
        vector<vector<State<pair<int,int>>>>::iterator i;
        vector<State<pair<int,int>>>::iterator j;
        for (i = myMatrix.begin(); i != myMatrix.end(); i++) {
            for (j = (*i).begin(); j != (*i).end(); j++) {
                myMatrix[(*j).getLoc().first][(*j).getLoc().second].setCameFrom(nullptr);
            }
        }
    }

    MatrixSearchable(vector<vector<State<pair<int,int>>>> matrix, State<pair<int,int>> start, State<pair<int,int>> final,
                        int row, int col) {
        myStart = start;
        myFinal = final;
        myMatrix = matrix;
        myRow = row;
        myCol = col;
    }
    State<pair<int,int>>* getInitialState(){
        return &myStart;
    }
    State<pair<int,int>>* getGoalState(){
        return &myFinal;
    }
    list<State<pair<int,int>>*> getAllPossibleStates(State<pair<int,int>>* s){
        int row = s->getLoc().first;
        int col = s->getLoc().second;
        list<State<pair<int,int>>*> possibleStates;
        State<pair<int,int>> tempState;
        if (row > 0) {
            tempState = myMatrix[row-1][col];
            if (tempState.getCost() != -1) {
                possibleStates.push_back(&myMatrix[row - 1][col]);
            }
        }
        if (col > 0) {
            tempState = myMatrix[row][col-1];
            if (tempState.getCost() != -1) {
                possibleStates.push_back(&myMatrix[row][col - 1]);
            }
        }
        if (row < myRow-1) {
            tempState = myMatrix[row+1][col];
            if (tempState.getCost() != -1) {
                possibleStates.push_back(&myMatrix[row + 1][col]);
            }
        }
        if (col < myCol-1) {
            tempState = myMatrix[row][col+1];
            if (tempState.getCost() != -1) {
                possibleStates.push_back(&myMatrix[row][col + 1]);
            }
        }
        return possibleStates;
    }
};


#endif //PROJECT2_MATRIXSEARCHABLE_H
