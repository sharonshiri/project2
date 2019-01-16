//
// Created by sharon on 15/01/19.
//

//#include "tryParallel.h"

#include "MyParallelServer.h"

struct params {
    pthread_t* myThread;
    MyParallelServer* myClass;
    int mySocket;
};

/*
 * Function Name: threadFunc
 * Input: void* arg
 * Output: void*
 * Function Operation: read as long as the simulator is on
 */

void* listenThreadFunc(void *arg) {
    // get this (threadFunc is C function, and we want to have Server functions)
    MyParallelServer* myServer = (MyParallelServer*) arg;
    myServer->listenAcceptThread();
    // return null pointer
    return nullptr;
}

void* readerThreadFunc(void *arg) {
    // get this (threadFunc is C function, and we want to have Server functions)
    params* myParam = (params*) arg;
    myParam->myClass->readerThread(myParam->mySocket, myParam->myThread);
    free(myParam);
    // return null pointer
    return nullptr;
}


void MyParallelServer::listenAcceptThread() {
    timeval timeout;
    timeout.tv_sec = 300;
    timeout.tv_usec = 0;

    if (listen(myListenSocket, SOMAXCONN) < 0) {
        throw runtime_error("listen failed");
    }
    while (continueGetClients) {
        setsockopt(myListenSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout,
                   sizeof(timeout));

        // accept
        int myClientSocket = (accept(myListenSocket,
                                     (struct sockaddr *) &address,
                                     (socklen_t *) &addrLen));

        if (myClientSocket < 0) {
            if (errno == EWOULDBLOCK) {
                stop();
                cout << "timeout!" << endl;
            }
        }else {
            // create the readerThread for the socket
            pthread_t* threadForClient = (pthread_t*) malloc(sizeof(pthread_t));
            params* myParams = (params*) malloc(sizeof(params));

            myParams->myClass = this;
            myParams->mySocket = myClientSocket;
            myParams->myThread = threadForClient;

            pthread_create(threadForClient, nullptr, readerThreadFunc, myParams);
            listOfReaderThreads.push_back(threadForClient);
        }
        timeout.tv_sec = 10;
    }
}

void MyParallelServer::readerThread(int socket, pthread_t* thread) {
    ssize_t readVars;
    char readBuffer[1025] = {0};

    string writeString="";
    string readString="";
    // continue read data from client
    do {
        // read from simulator
        readVars = read(socket, readBuffer, 1024);
        if (readVars > 0) {
            // use it as string, after the num of bits it is not relevant
            readBuffer[readVars] = 0;
            readString += readBuffer;
            myClientHandler->handleClient(readString, writeString);
        }
    } while (writeString.length() == 0);

    cout << "result === " << writeString << endl;
    send(socket, writeString.c_str(), writeString.length(), 0);
    listOfReaderThreads.remove(thread);
    free(thread);
    close(socket);
    if (listOfReaderThreads.empty() && !continueGetClients) {
        finishServer = true;
    }
}

void MyParallelServer::open(int port, ClientHandler* clientHandler) {
    myClientHandler = clientHandler;
    addrLen = sizeof(address);

    // creating socket file descriptor
    if ((myListenSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw runtime_error("socket failed");
    }

    memset(&address, '0', sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // do the bind
    if (bind(myListenSocket, (struct sockaddr *) &address, sizeof(address)) < 0) {
        throw runtime_error("bind failed");
    }

    pthread_create(&threadListenAllClients, nullptr, listenThreadFunc, this);
}


bool MyParallelServer::getFinishServer() {
    return finishServer;
}

void MyParallelServer::stop(){
    continueGetClients = false;
    if (listOfReaderThreads.empty() && !continueGetClients) {
        finishServer = true;
    }
}



/*
 * Function Name: ~Server
 * Input: -
 * Output: -
 * Function Operation: destructor
*/
MyParallelServer::~MyParallelServer() {
    // close listener
    close(myListenSocket);
    pthread_join(threadListenAllClients, nullptr);
}