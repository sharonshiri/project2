//
// Created by sharon on 11/01/19.
//


#include "Main.h"

int boot::Main::main(char* portS) {
    int port = atoi(portS);
    MatrixSolver* mySolver = new MatrixSolver();
    FileCacheManager* myFileCache = new FileCacheManager();
   // MyReverseClientHandler* myClientHandler = new MyReverseClientHandler();
    MyTestClientHandler* myClientHandler = new MyTestClientHandler(mySolver, myFileCache);
   // MySerialServer* mySerialServer = new MySerialServer();
   MyParallelServer* myParallelServer = new MyParallelServer();
    myParallelServer->open(port, myClientHandler);
   // StringReverse* mySolver = new StringReverse();
    while (1);
    return 0;
}