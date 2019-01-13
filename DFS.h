#ifndef PROJECT_DFS_H
#define PROJECT_DFS_H

#include <stack>
#include "Searcher.h"

template<class T>
class DFS : public Searcher<T>{
    list<State<T>*> visited;
    bool visitedContains(State<T>* state) {
        for (auto it: visited) {
            if(*it == *state) {
                return true;
            }
        }
        return false;
    }
public:
    list<State<T>*> search(Searchable<T>* s) {
        s->initializeMatrix();
        // Create a stack for DFS
        stack<State<T>*> myStack;
        // Push the current source node.
        State<T>* curr = s->getInitialState();
        myStack.push(curr);
        while (!myStack.empty()) {
            // Pop a vertex from stack and print it
            curr = myStack.top();
            myStack.pop();
            // Stack may contain same vertex twice. So
            // we need to print the popped item only
            // if it is not visited.
            if (!visitedContains(curr)) {
                if (visited.size() > 0) {
                    State<T>* last = visited.back();
                    curr->setCameFrom(last);
                }
                visited.push_back(curr);
                if(*curr == *(s->getGoalState())) {
                    break;
                }
            }
            // Get all adjacent vertices of the popped vertex s
            // If a adjacent has not been visited, then puah it
            // to the stack.
            list<State<T>*> adj = s->getAllPossibleStates(curr);
            if (!(adj.empty())) {
                for (auto i : adj) {
                    if (!visitedContains(i)) {
                        myStack.push(i);
                    }
                }
            } else {
                visited.clear();
                break;
            }
        }
        visited.reverse();
        return visited;
    }
};


#endif //PROJECT_DFS_H
