//
// Created by sharon on 11/01/19.
//

#include "Main.h"
using namespace boot;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        return 0;
    }
    boot::Main myMain;
    myMain.main(argv[1]);
    return 0;
}