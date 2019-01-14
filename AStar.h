//
// Created by sharon on 13/01/19.
//

#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

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
class AStar : public Searcher<T> {
    priority_queue<State<T>*,vector<State<T>*>, CmpStates<T>> myQueue;
    list<State<T>*> closed;
    double costTillCurr(State<T>* curr,State<T>* first){
        double totalCost = 0;
        while (!(*curr == *first)) {
            totalCost += curr->getCost();
            curr = curr->getCameFrom();
        }
        return totalCost;
    }
    list<State<T>*> backTrace(State<T>* state,State<T>* first) {
        list<State<T>*> trace;
        while (!(*state == *first)) {
            trace.push_back(state);
            state = state->getCameFrom();
        }
        trace.push_back(state);
        return trace;
    }
public:
    list<State<T>*> search(Searchable<T> *s) {
        s->initializeMatrix();
        State<T>* first = s->getInitialState();

        // inherited from Searcher
        myQueue.push(first);
        while (myQueue.size() > 0) {
            // inherited from Searcher, removes the best state
            State<T>* n = myQueue.top();
            myQueue.pop();
            closed.push_back(n);
            // private method, back traces through the parents
            // calling the delegated method, returns a list of states with n as a parent
            if (*n == *s->getGoalState()) {
                return backTrace(n, first);
            }
            list<State<T>*> succerssors = s->getAllPossibleStates(n);
            double currCost = costTillCurr(n,first) + 1;
            for (auto it : succerssors) {
                if (openListContains(it)) {
                    // find the real address of n, and set came from of it
                    if (costTillCurr(it, first) > currCost) {


                    }
                    updateCameFrom(it, n);
                    myQueue.push(it);
                } else {
                    if (!openListContains(it)) {
                        // find the real address of n, and update its came from
                        updateList(n, it);
                    }
                }
            }
        }
        list<State<T> *> empList;
        return empList;
    }
};
#endif //PROJECT2_ASTAR_H