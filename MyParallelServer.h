//
// Created by sharon on 13/01/19.
//

#ifndef PROJECT2_MYPARALLELSERVER_H
#define PROJECT2_MYPARALLELSERVER_H

#include "Server.h"
#include <queue>
#include <mutex>

using namespace server_side;

class MyParallelServer : public Server{
public:
    struct sockaddr_in address;
    int addrLen;
    void open(int port, ClientHandler* clientHandler);
    void stop();
    void listenAcceptThread();
    void handleClientThread();
    bool continueGetClients = true;
    bool continueHandleClients = true;
    pthread_t threadListenAllClients;
    pthread_t threadForClient;
    queue<int> clientSocketsQueue;
    mutex mtxForMyQueue;
    ~MyParallelServer();
};


#endif //PROJECT2_MYPARALLELSERVER_H
