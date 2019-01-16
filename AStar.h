//
// Created by sharon on 13/01/19.
//

#ifndef PROJECT2_ASTAR_H
#define PROJECT2_ASTAR_H

#include "Searcher.h"
#include <unordered_map>
#include <cmath>
#include <limits>

using namespace std;


template<class T>
class AStar : public Searcher<T> {
    list<State<T>*> open;
    list<State<T>*> closed;
    State<T>* final;
    State<T>* first;
    int numberOfNodes;
    double costOfNodes;
    unordered_map<State<T>*,double> gFuncStates;

    bool closeListContains(State<T>* state) {
        for (auto it : closed) {
            if (*state == *it) {
                return true;
            }
        }
        return false;
    }
    list<State<T>*> backTrace(State<T>* state) {
        list<State<T>*> trace;
        while (!(*state == *first)) {
            trace.push_back(state);
            state = state->getCameFrom();
        }
        trace.push_back(state);
        return trace;
    }
    bool openListContains(State<T>* state) {
        for (auto it : open) {
            if (*state == *it) {
                return true;
            }
        }
        return false;
    }
    void updateCameFrom(State<T>* node, State<T>* prev) {
        for (auto it : closed) {
            if (*prev == *it) {
                node->setCameFrom(prev);
            }
        }
    }
    State<T>* getMinNeigbour(list<State<T>*> neighboursNoInClose) {
        State<T>* minNeighbour;
        double minNeighbourCost =  numeric_limits<std::size_t>::max();
        for (auto it : neighboursNoInClose) {
            double fNewLeft = costTillCurr(it) + calculateDistance(it);
            if (fNewLeft < minNeighbourCost) {
                minNeighbourCost = fNewLeft;
                minNeighbour = it;
            }
        }
        return minNeighbour;
    }
    double calculateDistance(State<T>* curr) {
        double xCurr = curr->getLoc().first;
        double yCurr = curr->getLoc().second;
        double xFinal = final->getLoc().first;
        double yFinal = final->getLoc().second;
        double h = abs(xCurr - xFinal) + abs(yCurr - yFinal);
        return h;
    }
    double costTillCurr(State<T>* curr){
        if (gFuncStates.find(curr) != gFuncStates.end()) {
            return gFuncStates[curr];
        }
        double totalCost = 0;
        while (!(*curr == *first)) {
            totalCost += curr->getCost();
            curr = curr->getCameFrom();
            if (curr == nullptr) {
                break;
            }
        }
        totalCost += first->getCost();
        return totalCost;
    }
    void updateList(State<T>* node, State<T>* prev) {
        for (auto it : closed) {
            if (*node == *it) {
                node->setCameFrom(prev);
            }
        }
    }
    void popCurrFromList(State<T>* curr) {
        for (auto it : open) {
            if (*it == *curr) {
                open.remove(it);
                break;
            }
        }
    }

public:
    list<State<T>*> search(Searchable<T> *s) {
        s->initializeMatrix();
        numberOfNodes = 0;
        costOfNodes = 0;
        // inherited from Searcher, removes the best state
        first = s->getInitialState();
        final = s->getGoalState();
        // inherited from Searcher
        open.push_back(first);
        while (open.size() > 0){
            State<T>* n = getMinNeigbour(open);
            numberOfNodes++;
            costOfNodes+= n->getCost();
            popCurrFromList(n);
            closed.push_back(n);
            // private method, back traces through the parents
            // calling the delegated method, returns a list of states with n as a parent
            if (*n == *s->getGoalState()) {
                return backTrace(n);
            }
            list<State<T>*> succerssors = s->getAllPossibleStates(n);
            for (auto it : succerssors) {
                if (!closeListContains(it) && !openListContains(it)) {
                    // find the real address of n, and set came from of it
                    updateCameFrom(it,n);
                    open.push_back(it);
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
#endif //PROJECT2_ASTAR_H