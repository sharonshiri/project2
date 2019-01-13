//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_MYSERIALSERVER_H
#define PROJECT2_MYSERIALSERVER_H

#include "Server.h"
#include <pthread.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <mutex>

class MySerialServer : public Server{
    int myListenSocket;
    int myClientSocket;
    pthread_t waitForClient;
    ClientHandler* myClientHandler;
public:
    struct sockaddr_in address;
    int addrLen;
    void open(int port, ClientHandler* handler);
    void stop();
    ClientHandler* getClientHandler();
    bool continueThread = true;
    int getClientSocket();
    int getListenSocket();
    void myThread();
    void setClientSocket(int);
    ~MySerialServer();
};


#endif //PROJECT2_MYSERIALSERVER_H
