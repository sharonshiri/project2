//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_CHACHEMANAGER_H
#define PROJECT2_CHACHEMANAGER_H

#include <string>
using namespace std;

class CacheManager {
public:
    virtual string getSolution(string) = 0;
    virtual void saveInCache(string,string) = 0;
    virtual ~CacheManager() = default;
};


#endif //PROJECT2_CHACHEMANAGER_H
