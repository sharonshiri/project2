#ifndef PROJECT2_TRYPARALLEL_H
#define PROJECT2_TRYPARALLEL_H

#include "Server.h"
#include <queue>
#include <mutex>
#include <list>

using namespace server_side;

class MyParallelServer : public Server{
    bool finishServer = false;
public:
    struct sockaddr_in address;
    int addrLen;
    void open(int port, ClientHandler* clientHandler);
    void stop();
    void listenAcceptThread();
    void readerThread(int,pthread_t*);
    bool continueGetClients = true;
    pthread_t threadListenAllClients;
    list <pthread_t*>  listOfReaderThreads;
    bool getFinishServer();
    ~MyParallelServer();
};

#endif //PROJECT2_TRYPARALLEL_H