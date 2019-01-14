//
// Created by sharon on 11/01/19.
//

#include "MyTestClientHandler.h"


MyTestClientHandler::MyTestClientHandler(Solver* solver, CacheManager* cache) {
    myCacheManager = cache;
    mySolver = solver;
}

void MyTestClientHandler::handleClient(string read, string& write) {
    problem += read;
    if (problem.find("end") != string::npos) {
        problem = problem.substr(0, problem.find("end"));
        deleteSpaces();
        string solution = myCacheManager->getSolution(problem);
        if (solution.length() > 0)
        {
            write = solution;
        } else {
            solution = mySolver->solve(problem);
            myCacheManager->saveInCache(problem, solution);
            write = solution;
        }
        problem = "";
    }
}

void MyTestClientHandler::deleteSpaces() {
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