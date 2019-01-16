//
// Created by sharon on 12/01/19.
//

#include "MatrixSolution.h"

/*MatrixSolution::MatrixSolution() {
    myList = list;

}*/

double MatrixSolution::calcCost(list<State<pair<int,int>>*> list) {
    double cost = 0;
    for (auto it : list) {
        cost += it->getCost();
    }
    return cost;
}

string MatrixSolution::getPairString(list<State<pair<int,int>>*> list, Searcher<pair<int,int>>* searcher) {
    string pair = "";

    pair = to_string(calcCost(list)) + "," + to_string(searcher->getNumberOfNodesEvaluated());
    return pair;
}

pair<double,int> MatrixSolution::getPair(list<State<pair<int,int>>*> list, Searcher<pair<int,int>>* searcher) {
    pair<double,int> myPair = make_pair(calcCost(list), searcher->getNumberOfNodesEvaluated());
    return myPair;
}


string MatrixSolution::getDirectionString(list<State<pair<int,int>>*> myList) {
    string direction = "";
    // list is from the start to final
    if (myList.empty()) {
        return "-1";
    }
    list<State<pair<int,int>>*>::iterator it1 = myList.begin();
    list<State<pair<int,int>>*>::iterator it2 = myList.begin();
    it2++;
    while (it2 != myList.end()) {
        direction = getCurrDirection(*it2, *it1) + "," + direction;
        it1++;
        it2++;
    }

   direction.erase(direction.length() - 1,1);
   return direction;
}

string MatrixSolution::getCurrDirection(State<pair<int,int>>* first, State<pair<int,int>>* second) {
    int firstI = first->getLoc().first;
    int firstJ = first->getLoc().second;
    int secondI = second->getLoc().first;
    int secondJ = second->getLoc().second;
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
    return "";
}