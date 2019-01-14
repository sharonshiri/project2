//
// Created by sharon on 11/01/19.
//

#include "MySerialServer.h"
#include <streambuf>



/*
 * Function Name: threadFunc
 * Input: void* arg
 * Output: void*
 * Function Operation: read as long as the simulator is on
 */
void* threadFunc(void *arg) {
    // get this (threadFunc is C function, and we want to have Server functions)
    MySerialServer* myServer = (MySerialServer*) arg;
    myServer->myThread();
    // return null pointer
    return nullptr;
}

void MySerialServer::myThread() {
    timeval timeout;
    timeout.tv_sec = 3000;
    timeout.tv_usec = 0;
        int readVars;
        //continue get clients
        while (continueThread) {
            char readBuffer[1025] = {0};
            string writeString = "";
            string readString = "";
            if (listen(myListenSocket, 1) < 0) {
                throw runtime_error("listen failed");
            }

            setsockopt(myListenSocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

            // accept
            myClientSocket = (accept(myListenSocket, (struct sockaddr *) &address,
                                             (socklen_t *) &addrLen));

            if (myClientSocket< 0) {
                if (errno == EWOULDBLOCK)	{
                    stop();
                    cout << "timeout!" << endl;
                }	else	{
                    throw runtime_error("accept failed");
                }
            }
            else {
                // continue read data from client
                do {
                    // read from simulator
                    readVars = read(myClientSocket, readBuffer, 1024);
                    if (readVars > 0) {
                        // use it as string, after the num of bits it is not relevant
                        readBuffer[readVars] = 0;
                        readString = readBuffer;
                        myClientHandler->handleClient(readString, writeString);
                    }
                } while (writeString.length() == 0);
                cout << "result === " << writeString << endl;
                send(myClientSocket, writeString.c_str(), writeString.length(), 0);
            }
            // prepare to next client
            if (myClientSocket != -1) {
                close(myClientSocket);
            }
            timeout.tv_sec = 10;
        }
}


/*
 * Function Name: createServer
 * Input: double port
 * Output: -
 * Function Operation: create the sockets and thread
 */
void MySerialServer::open(int port, ClientHandler* clientHandler) {
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

    // create the thread
    pthread_create(&waitForClient, nullptr, threadFunc, this);

}


void MySerialServer::stop() {
    delete(this);
}

/*
 * Function Name: ~Server
 * Input: -
 * Output: -
 * Function Operation: destructor
 */
MySerialServer::~MySerialServer() {
    continueThread = false;
    close(myListenSocket);
    pthread_join(waitForClient, nullptr);
}