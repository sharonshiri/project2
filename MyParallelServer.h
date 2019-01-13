//
// Created by sharon on 13/01/19.
//

#ifndef PROJECT2_MYPARALLELSERVER_H
#define PROJECT2_MYPARALLELSERVER_H

#include "Server.h"
class MyParallelServer : public Server{
public:
    void open(int port, ClientHandler* handler);
    void stop();
};


#endif //PROJECT2_MYPARALLELSERVER_H
