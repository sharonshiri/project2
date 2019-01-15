//
// Created by hadar on 1/8/19.
//

#ifndef PROJECT_BESTFIRSTSEARCH_H
#define PROJECT_BESTFIRSTSEARCH_H

#include <queue>
#include "Searcher.h"


template<class T>
struct CmpStates
{
    bool operator()(const State<T>* left, const State<T>* right) const
    {
        return *left > *right;
    }
};

template<class T>
class BestFirstSearch : public Searcher<T>{
    priority_queue<State<T>*,vector<State<T>*>, CmpStates<T>> myQueue;
    list<State<T>*> closed;
    int numberOfNodes;
    double costOfNodes;
    list<State<T>*> backTrace(State<T>* state,State<T>* first) {
        list<State<T>*> trace;
        while (!(*state == *first)) {
            trace.push_back(state);
            state = state->getCameFrom();
        }
        trace.push_back(state);
        return trace;
    }
    bool openListContains(State<T>* state) {
        priority_queue<State<T>*,vector<State<T>*>, CmpStates<T>
               /* ,std::greater<State<T>*>*/> tempQueue = myQueue;
        while (tempQueue.size() > 0) {
            State<T>* temp = tempQueue.top();
            if(*temp == *state) {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }
    bool closeListContains(State<T>* state) {
        for (auto it : closed) {
            if (*state == *it) {
                return true;
            }
        }
        return false;
    }
    void updateList(State<T>* node, State<T>* prev) {
        for (auto it : closed) {
            if (*node == *it) {
                node->setCameFrom(prev);
            }
        }
    }
    void updateCameFrom(State<T>* node, State<T>* prev) {
        for (auto it : closed) {
            if (*prev == *it) {
                node->setCameFrom(prev);
            }
        }
    }


public:
    list<State<T>*> search(Searchable<T>* s) {
        numberOfNodes = 0;
        costOfNodes =0;
        s->initializeMatrix();
        // inherited from Searcher
        myQueue.push(s->getInitialState());
        while (myQueue.size() > 0) {
            // inherited from Searcher, removes the best state
            State<T>* n = myQueue.top();
            numberOfNodes++;
            costOfNodes+= n->getCost();
            myQueue.pop();
            closed.push_back(n);
            // private method, back traces through the parents
            // calling the delegated method, returns a list of states with n as a parent
            if (*n == *s->getGoalState()) {
                return backTrace(n,s->getInitialState());
            }
            list<State<T>*> succerssors = s->getAllPossibleStates(n);
            for (auto it : succerssors) {
                if (!closeListContains(it) && !openListContains(it)) {
                    // find the real address of n, and set came from of it
                    updateCameFrom(it,n);
                    myQueue.push(it);
                } else {
                    if(!openListContains(it)) {
                        // find the real address of n, and update its came from
                        updateList(n,it);
                    }
                }
            }
        }
        list<State<T>*> empList;
        return empList;
    }
    int getNumberOfNodesEvaluated() {
        return numberOfNodes;
    }
    double getCostEvaluated() {
        return costOfNodes;
    }
};


#endif //PROJECT_BESTFIRSTSEARCH_H