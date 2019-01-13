//
// Created by sharon on 12/01/19.
//

#include "MatrixSolution.h"

MatrixSolution::MatrixSolution(list<State<pair<int,int>>> list) {
    myList = list;
    cost = 0;
    for (auto it : myList) {
        cost += it.getCost();
    }
}

double MatrixSolution::getCostOfTrace() {
    return cost;
}

string MatrixSolution::getPairString() {
    string pair = "";
    pair = to_string(cost) + "," + to_string(myList.size());
    return pair;
}

string MatrixSolution::getDirectionString() {
    string direction = "";
    // list is from the start to final
    // reverse list
   myList.reverse();
   State<pair<int,int>> currState = *myList.begin();
   while (currState.getCameFrom() != nullptr) {
       direction = getCurrDirection(*currState.getCameFrom(), currState) + "," + direction;
       currState = *currState.getCameFrom();
   }
   direction.erase(direction.length() - 1,1);
   return direction;
}

string MatrixSolution::getCurrDirection(State<pair<int,int>> first, State<pair<int,int>> second) {
    int firstI = first.getLoc().first;
    int firstJ = first.getLoc().second;
    int secondI = second.getLoc().first;
    int secondJ = second.getLoc().second;
    if (firstI > secondI) {
        return "Up";
    }
    if (firstI < secondI) {
        return "Down";
    }
    if (firstJ > secondJ) {
        return "Left";
    }
    if (firstJ < secondJ) {
        return "Right";
    }
}

bool MatrixSolution::operator<(MatrixSolution other) {
    if (cost < other.cost) {
        return true;
    }
    return false;
}