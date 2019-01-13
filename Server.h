//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_SERVER_H
#define PROJECT2_SERVER_H

#include "ClientHandler.h"

class Server {
    virtual void open(int port, ClientHandler* MyHandler) = 0;
    virtual void stop() = 0;
};
#endif //PROJECT2_SERVER_H
