//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_CLIENTHANDLER_H
#define PROJECT2_CLIENTHANDLER_H

#include <iostream>

using namespace std;

class ClientHandler {
public:
    virtual void handleClient(string read, string& write) = 0;
};
#endif //PROJECT2_CLIENTHANDLER_H
