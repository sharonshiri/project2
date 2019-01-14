//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

#include "Server.h"


using namespace server_side;

class MySerialServer : public Server{

public:
    struct sockaddr_in address;
    int addrLen;
    void open(int port, ClientHandler* handler);
    void stop();
    bool continueThread = true;
    int myClientSocket;
    pthread_t waitForClient;
    void myThread();
    ~MySerialServer();
};


#endif //PROJECT2_MYSERIALSERVER_H
