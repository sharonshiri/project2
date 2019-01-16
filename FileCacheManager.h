//
// Created by sharon on 11/01/19.
//

#ifndef PROJECT2_FILECACHEMANAGER_H
#define PROJECT2_FILECACHEMANAGER_H

#include "CacheManager.h"
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <mutex>

class FileCacheManager : public CacheManager{
    unordered_map<string,string> myMap;
    string solutionsFile = "solutionFile.txt";
    string allProblemSolution = "";
    void parseFile(string line);
    void loadToMap();
    mutex mtxForSave;
public:
    FileCacheManager();
    string getSolution(string);
    void saveInCache(string,string);
    ~FileCacheManager() = default;
};


#endif //PROJECT2_FILECACHEMANAGER_H
