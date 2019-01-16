#ifndef PROJECT_BFS_H
#define PROJECT_BFS_H

#include "Searcher.h"

template<class T>
class BFS : public Searcher<T> {
    list<State<T>*> visited;
    queue<State<T>*> myQueue;
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
    bool visitedContains(State<T>* state) {
        for (auto it: visited) {
            if(*it == *state) {
                return true;
            }
        }
        return false;
    }
    bool myQueueContains(State<T>* state) {
        queue<State<T>*> tempQueue = myQueue;
        while (tempQueue.size() > 0) {
            State<T>* temp = tempQueue.front();
            if(*temp == *state) {
                return true;
            }
            tempQueue.pop();
        }
        return false;
    }

public:
    list<State<T>*> search(Searchable<T>* s) {
        s->initializeMatrix();
        numberOfNodes = 0;
        costOfNodes = 0;
        // Mark the current node as visited and enqueue it
        State<T>* curr = s->getInitialState();
        myQueue.push(curr);
        // vertices of a vertex
        while(!myQueue.empty())
        {
            // Dequeue a vertex from queue and print it
            curr = myQueue.front();
            numberOfNodes++;
            costOfNodes += curr->getCost();
            if(*curr == *(s->getGoalState())){
                return backTrace(curr,s->getInitialState());
            }
            myQueue.pop();
            list<State<T>*> adj = s->getAllPossibleStates(curr);
            visited.push_back(curr);
            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            // 'i' will be used to get all adjacent
            for (auto i : adj)
            {
                if (!visitedContains(i) && !myQueueContains(i))
                {
                    i->setCameFrom(curr);
                    myQueue.push(i);
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


#endif //PROJECT_BFS_H
