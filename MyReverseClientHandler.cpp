//
// Created by sharon on 12/01/19.
//

#include "MyReverseClientHandler.h"


void MyReverseClientHandler::handleClient(string read, string& write) {
    if (collectProblem(read)) {
        // get it from cache
        // if not in cache, then
        string temp = mySolver->solve(problem);
        write = temp;
        // save in cache
    }
}

/*
 * Function Name: parserOfVars
 * Input: string &Message
 * Output: void
 * Function Operation: parse the buffer and update the map
 */
bool MyReverseClientHandler::collectProblem(string buffer) {
    stringToParse += buffer;
    string completeMessage;
    // check if receive buffer has a complete message
    completeMessage = getCompleteMessage();
    if (completeMessage.length() > 0) {
        problem = completeMessage;
        return true;
    }
    return false;
}

string MyReverseClientHandler::getCompleteMessage() {
    int rc = stringToParse.find('\n');
    string temp = "";
    // if there is no '\n', return empty string
    if (rc < 0)
        return temp;
    // otherwise, we have a message
    temp = stringToParse.substr(0, rc);
    // update the remain
    stringToParse = stringToParse.substr(rc + 1, stringToParse.length());
    // return the message until \n
    return temp;
}

void MyReverseClientHandler::setSolver(Solver* solver) {
    mySolver = solver;
}
