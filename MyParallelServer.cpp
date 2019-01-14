//
// Created by sharon on 13/01/19.
//


#include "MyParallelServer.h"

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

void* handleThreadFunc(void *arg) {
    // get this (threadFunc is C function, and we want to have Server functions)
    MyParallelServer* myServer = (MyParallelServer*) arg;
    myServer->handleClientThread();
    // return null pointer
    return nullptr;
}


void MyParallelServer::listenAcceptThread() {
    timeval timeout;
    timeout.tv_sec = 3000;
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

        cout << myClientSocket << " accepeted!" << endl;

        if (myClientSocket < 0) {
            if (errno == EWOULDBLOCK) {
                stop();
                cout << "timeout!" << endl;
            } else {
                throw runtime_error("accept failed");
            }
        }
        else {

            // start of lock
            mtxForMyQueue.lock();
            clientSocketsQueue.push(myClientSocket);
            // unlock
            mtxForMyQueue.unlock();
        }
        timeout.tv_sec = 30;
    }
}

void MyParallelServer::handleClientThread() {
    ssize_t readVars;
    char readBuffer[1025] = {0};


    while((!(clientSocketsQueue.empty()) || continueHandleClients)) {
        if (!(clientSocketsQueue.empty())){
            mtxForMyQueue.lock();
            int tempSocket = clientSocketsQueue.front();
            clientSocketsQueue.pop();
            mtxForMyQueue.unlock();
            string writeString="";
            string readString="";
            // continue read data from client
            do {
                cout << " reading from " << tempSocket << endl;

                // read from simulator
                readVars = read(tempSocket, readBuffer, 1024);
                cout << "read " << readVars << endl;

                if (readVars > 0) {
                    // use it as string, after the num of bits it is not relevant
                    readBuffer[readVars] = 0;
                    readString = readBuffer;
                    cout << "before handle client" << endl;
                    cout << readString << endl;
                    cout << writeString << endl;
                    myClientHandler->handleClient(readString, writeString);
                    cout << "after handle client" << endl;
                }
            } while (writeString.length() == 0);
            cout << "result === " << writeString << endl;
            send(tempSocket, writeString.c_str(), writeString.length(), 0);

            if (tempSocket != -1) {
                close(tempSocket);
            }
        } else {
            usleep(100000);
        }
    }
    delete(this);
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
    // create the thread
    pthread_create(&threadForClient, nullptr, handleThreadFunc, this);
}

void MyParallelServer::stop(){
    continueGetClients = false;
}

/*
 * Function Name: ~Server
 * Input: -
 * Output: -
 * Function Operation: destructor
 */
MyParallelServer::~MyParallelServer() {
    close(myListenSocket);
    pthread_join(threadListenAllClients, nullptr);
    pthread_join(threadForClient, nullptr);
}