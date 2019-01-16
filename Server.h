//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_SERVER_H
#define PROJECT2_SERVER_H

#include "ClientHandler.h"
#include <pthread.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <mutex>

namespace server_side {
    class Server {
    protected:
        int myListenSocket;
        ClientHandler* myClientHandler;
    public:
        void virtual open(int port, ClientHandler *MyHandler) = 0;
        void virtual stop() = 0;
        virtual ~Server() = default;
    };
}
#endif //PROJECT2_SERVER_H
