//
// Created by sharon on 11/01/19.
//

#include "MyParallelServer.h"
#include "Main.h"

int boot::Main::main(char* portS) {
    int port = atoi(portS);
    MatrixSolver* mySolver = new MatrixSolver();
    FileCacheManager* myFileCache = new FileCacheManager();
    MyTestClientHandler* myClientHandler = new MyTestClientHandler(mySolver, myFileCache);
    MyParallelServer* parallelServer = new MyParallelServer();
    parallelServer->open(port, myClientHandler);
    while (!parallelServer->getFinishServer());
    delete(parallelServer);
    delete(mySolver);
    delete(myFileCache);
    delete(myClientHandler);
    return 0;
}