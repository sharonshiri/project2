//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_MYTESTCLIENTHANDLER_H
#define PROJECT2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include <string>

using namespace std;

class MyTestClientHandler : public ClientHandler {
    Solver* mySolver;
    CacheManager* myCacheManager;
    bool collectProblem(string);
    string stringToParse = "";
    string getCompleteMessage();
    string problem = "";
public:
    MyTestClientHandler (Solver*, CacheManager*);
    void handleClient(string read, string &write);
};


#endif //PROJECT2_MYTESTCLIENTHANDLER_H
