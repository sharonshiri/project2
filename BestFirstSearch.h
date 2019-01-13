//
// Created by hadar on 1/8/19.
//

#ifndef PROJECT_BESTFIRSTSEARCH_H
#define PROJECT_BESTFIRSTSEARCH_H

#include <queue>
#include <unordered_set>
#include "Searcher.h"

template<class T>
class BestFirstSearch : public Searcher<T>{
    priority_queue<State<T>,vector<State<T>>,std::greater<State<T>>> myQueue;
    unordered_set<State<T>> closed;
    list<State<T>> backTrace(State<T> state,State<T> first) {
        list<State<T>> trace;
        while (!(state == first)) {
            trace.push_back(state);
            state = state.getCameFrom();
        }
        trace.push_back(state);
        return trace;
    }
    bool openListContains(State<T> state) {
        priority_queue<State<T>,vector<State<T>>
                ,std::greater<State<T>>> tempQueue = myQueue;
        while (tempQueue.size() > 0) {
            State<T> temp = tempQueue.top();
            if(temp == state) {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }
public:
    list<State<T>> search(Searchable<T>* s) {
        // inherited from Searcher
        myQueue.push(s->getInitialState());
        while (myQueue.size() > 0) {
            // inherited from Searcher, removes the best state
            State<T> n = myQueue.top();
            myQueue.pop();
            closed.insert(n);
            // private method, back traces through the parents
            // calling the delegated method, returns a list of states with n as a parent
            if (n == s->getGoalState()) {
                return backTrace(n,s->getInitialState());
            }
            list<State<T>> succerssors = s->getAllPossibleStates(n);
            for (auto it : succerssors) {
                if ((closed.find(it) == closed.end()) && !openListContains(it)) {
                    (it).setCameFrom(n);
                    myQueue.push(it);
                } else {
                    if(!openListContains(it)) {
                        myQueue.push(it);
                    }
                }
            }
        }
    }
};


#endif //PROJECT_BESTFIRSTSEARCH_H
