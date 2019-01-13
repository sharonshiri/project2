//
// Created by sharon on 11/01/19.
//


#include "Main.h"

int boot::Main::main(char* portS) {
    int port = atoi(portS);
   // MyReverseClientHandler* myClientHandler = new MyReverseClientHandler();
    MyTestClientHandler* myClientHandler = new MyTestClientHandler();
    MySerialServer* mySerialServer = new MySerialServer();
    mySerialServer->open(port, myClientHandler);
   // StringReverse* mySolver = new StringReverse();
    MatrixSolver* mySolver = new MatrixSolver();
    myClientHandler->setSolver(mySolver);
    while (1);
    return 0;
}