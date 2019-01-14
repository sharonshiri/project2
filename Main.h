//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_MYMAIN_H
#define PROJECT2_MYMAIN_H

#include <cstdlib>
#include "MySerialServer.h"
#include "MyParallelServer.h"

#include "MyTestClientHandler.h"
#include "MatrixSolver.h"

#include "MyReverseClientHandler.h"
#include "StringReverse.h"

#include "FileCacheManager.h"

using namespace std;

namespace boot {
    class Main {
    public:
        int main(char*);
    };
}


#endif //PROJECT2_MYMAIN_H
