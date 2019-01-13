
#ifndef PROJECT_SEARCHER_H
#define PROJECT_SEARCHER_H

#include <queue>
#include "Searchable.h"

template<class T>
class Searcher {
public:
    virtual list<State<T>*> search(Searchable<T>*) = 0;
};
#endif //PROJECT_SEARCHER_H
