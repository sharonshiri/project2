//
// Created by sharon on 11/01/19.
//

#include "MyTestClientHandler.h"


MyTestClientHandler::MyTestClientHandler(Solver* solver, CacheManager* cache) {
    myCacheManager = cache;
    mySolver = solver;
}

void MyTestClientHandler::handleClient(string read, string& write) {
    write = "";
    if (read.find("end") != string::npos) {
        cout << read << endl;
        read = read.substr(0, read.find("end"));
        deleteSpaces(read);
        string solution = myCacheManager->getSolution(read);
        if (solution.length() > 0)
        {
            write = solution;
        } else {
            solution = mySolver->solve(read);
            myCacheManager->saveInCache(read, solution);
            write = solution;
        }
        read = "";
    }
}

void MyTestClientHandler::deleteSpaces(string problem) {
    while (problem.length() > 0) {
        unsigned long rc = problem.find(' ');
        if (rc != string::npos) {
            problem.erase(rc, 1);
        } else {
            // no more spaces, break
            break;
        }
    }
}