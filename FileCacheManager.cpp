//
// Created by sharon on 11/01/19.
//

#include "FileCacheManager.h"

FileCacheManager::FileCacheManager() {
    loadToMap();
}

void FileCacheManager::loadToMap() {
    string line = "";
    fstream file;
    file.open(solutionsFile);
    if (file.is_open()) {
        // while there are more lines
        while (getline(file, line)) {
            // take care of one line from the text
            line = line + '\n';
            parseFile(line);
        }
    } else {
        file.open(solutionsFile, ios::out);
    }
    file.flush();
    file.close();
}

void FileCacheManager::parseFile(string line) {
    if (line != "$$\n") {
        allProblemSolution += line;
    } else {
        string problem = allProblemSolution.substr(0, allProblemSolution.find('$'));
        string solution = allProblemSolution.substr(allProblemSolution.find('$') + 2);
        myMap.insert(make_pair(problem,solution));
        allProblemSolution = "";
    }
}

string FileCacheManager::getSolution(string problem) {
    if (myMap.find(problem) != myMap.end()) {
        return myMap.find(problem)->second;
    } else {
        return "";
    }
}

void FileCacheManager::saveInCache(string problem, string solution) {
    //save to map
    myMap.insert(make_pair(problem,solution));
    //save to file
    fstream file;
    file.open(solutionsFile, ios::app);
    if (!(file.is_open())) {
        file.open(solutionsFile, ios::trunc | ios::out);
    }
    file << problem << "$\n" << solution << "\n$$\n";
    file.flush();
    file.close();
}
