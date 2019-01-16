//
// Created by sharon on 12/01/19.
//

#include "MatrixSolver.h"

string MatrixSolver::solve(string myString) {
    mtxForSolver.lock();
    myMatrix.clear();
    rowNumber = count(myString.begin(), myString.end(), '\n') - 2;
    createMatrix(myString);
    string startString = parseStartState(myString);
    string finalString = parseFinalState(myString);
    State<pair<int, int>> start = getStateFromMatrix(startString);
    State<pair<int, int>> final = getStateFromMatrix(finalString);
    string finalWay = findShortestWay(start, final);
    mtxForSolver.unlock();
    return finalWay;
}


string MatrixSolver::parseStartState(string &myString) {
    unsigned long rc = myString.find('\n');
    string myStartString = myString.substr(0, rc);
    myString.erase(0,rc+1);
    return myStartString;
}

string MatrixSolver::parseFinalState(string &myString){
    unsigned long rc = myString.find('\n');
    string myFinalString = myString.substr(0, rc);
    myString.erase(0,rc+1);
    return myFinalString;
}

void MatrixSolver::createMatrix(string &myString) {
    int tempRowNum = 0;
    string oneRow = "";
    while (tempRowNum < rowNumber) {
        unsigned long rc = myString.find('\n');
        oneRow = myString.substr(0, rc + 1);
        vector<State<pair<int, int>>> temp = parseOneRow(oneRow, tempRowNum);
        myMatrix.push_back(temp);
        // get ready for next row
        myString = myString.substr(rc + 1, myString.length());
        tempRowNum++;
    }
}



string MatrixSolver::getParam(string &message) {
    string param;
    unsigned long rc = message.find(',');
    // check if there is ','
    if (rc != string::npos) {
        // the param is until ','
        param = message.substr(0, rc);
        // update the rest of the message
        message = message.substr(rc + 1, message.length());
    } else {
        // if this is the last param
        param = message.substr(0, message.find('|'));
        message = "";
    }
    // return param
    return param;
}

vector<State<pair<int, int>>> MatrixSolver::parseOneRow(string myRow, int row) {
    vector<State<pair<int, int>>> myRowVec;
    string oneState;
    int col = 0;
    while (myRow.length() > 0) {
        oneState = getParam(myRow);
        double tempCost = stod(oneState);
        pair<int, int> tempLoc = make_pair(row, col);
        State<pair<int, int>> tempState(tempLoc, tempCost);
        myRowVec.push_back(tempState);
        col++;
    }
    colNumber = col;
    return myRowVec;
}

State<pair<int, int>> MatrixSolver::getStateFromMatrix(string loc) {
    int i = stoi(loc.substr(0,loc.find(',')));
    loc.erase(0,loc.find(',') +1 );
    int j = stoi(loc);
    if (i > rowNumber || j > colNumber) {
        // if not found location in matrix
        throw invalid_argument("location is not found");
    }
    return myMatrix[i][j];
}

string MatrixSolver::findShortestWay(State<pair<int, int>> start,State<pair<int, int>> final) {


    MatrixSearchable<pair<int,int>> mySearchable(myMatrix,start,final,rowNumber,colNumber);

    DFS<pair<int,int>> myDFS;
    BestFirstSearch<pair<int,int>> myBestFirst;
    BFS<pair<int,int>> myBFS;
    AStar<pair<int,int>> myAStar;

    list<State<pair<int,int>>*> tempList1 = myDFS.search(&mySearchable);
    list<State<pair<int,int>>*> tempList2 = myBestFirst.search(&mySearchable);
    list<State<pair<int,int>>*> tempList3 = myBFS.search(&mySearchable);
    list<State<pair<int,int>>*> tempList4 = myAStar.search(&mySearchable);

    MatrixSolution mySolution;
    cout << "DFS:\n" <<mySolution.getDirectionString(tempList1) << endl;
    cout << mySolution.getPairString(tempList1, &myDFS) << endl;


    cout << "BFS:\n"<< mySolution.getDirectionString(tempList3) << endl;
    cout << mySolution.getPairString(tempList3, &myBFS) << endl;

    cout << "BEST_FIRST:\n"<< mySolution.getDirectionString(tempList2) << endl;
    cout << mySolution.getPairString(tempList2, &myBestFirst) << endl;

    cout << "ASTAR:\n"<< mySolution.getDirectionString(tempList4) << endl;
    cout << mySolution.getPairString(tempList4,&myAStar) << endl;

    list<pair<int,list<State<pair<int,int>>*>>> myList;
    myList.push_back(make_pair(myDFS.getNumberOfNodesEvaluated(), tempList1));
    myList.push_back(make_pair(myBestFirst.getNumberOfNodesEvaluated(), tempList2));
    myList.push_back(make_pair(myBFS.getNumberOfNodesEvaluated(), tempList3));
    myList.push_back(make_pair(myAStar.getNumberOfNodesEvaluated(), tempList4));


    string minSolution = chooseBestAlg(myList);
    return minSolution;
}

string MatrixSolver::chooseBestAlg(list<pair<int,list<State<pair<int,int>>*>>> myList) {
    MatrixSolution mySolution;
    int minNodes = myList.front().first;
    list<State<pair<int,int>>*> minList = myList.front().second;
    double minCost = mySolution.calcCost(minList);
    for (auto it : myList) {
        if (!(it.second.empty())) {
            if (mySolution.calcCost(it.second) <= minCost) {
                if (mySolution.calcCost(it.second) == minCost) {
                    if (it.first < minNodes) {
                        minList = it.second;
                        minNodes = it.first;
                        minCost = mySolution.calcCost(it.second);
                    }
                } else {
                    minList = it.second;
                    minNodes = it.first;
                    minCost = mySolution.calcCost(it.second);
                }
            }
        }
    }
    return mySolution.getDirectionString(minList);
}