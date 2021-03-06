//
// Created by sharon on 12/01/19.
//

#ifndef PROJECT2_MYREVERSECLIENTHANDLER_H
#define PROJECT2_MYREVERSECLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

class MyReverseClientHandler : public ClientHandler{
    Solver* mySolver;
    //CacheManager* myCacheManager;
    bool collectProblem(string);
    string stringToParse = "";
    string getCompleteMessage();
    string problem = "";
public:
    void handleClient(string read, string &write);
    void setSolver(Solver*);
    ~MyReverseClientHandler() = default;
};


#endif //PROJECT2_MYREVERSECLIENTHANDLER_H
