//
// Created by sharon on 11/01/19.
//

#include "MyTestClientHandler.h"


void MyTestClientHandler::handleClient(string read, string& write) {
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
bool MyTestClientHandler::collectProblem(string buffer) {
    stringToParse += buffer;
    string completeMessage;
    // check if receive buffer has a complete message
    completeMessage = getCompleteMessage();
    while (completeMessage.length() > 0) {
        if (completeMessage == "end") {
              return true;
        } else {
            problem += completeMessage + "|";
        }
        // check if more complete messages in buffer
        completeMessage = getCompleteMessage();
    }
    return false;
}

string MyTestClientHandler::getCompleteMessage() {
    unsigned long rc = stringToParse.find('\n');
    string temp = "";
    // if there is no '\n', return empty string
    if (rc == string::npos)
        return temp;
    // otherwise, we have a message
    temp = stringToParse.substr(0, rc);
    // update the remain
    stringToParse = stringToParse.substr(rc + 1, stringToParse.length());
    // return the message until \n
    return temp;
}

void MyTestClientHandler::setSolver(Solver* solver) {
    mySolver = solver;
}
