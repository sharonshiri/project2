#ifndef PROJECT_BFS_H
#define PROJECT_BFS_H

#include "Searcher.h"

template<class T>
class BFS : public Searcher<T> {
    list<State<T>> visited;
public:
    list<State<T>> search(Searchable<T>* s) {
        // Create a queue for BFS
        queue<State<T>> myQueue;
        // Mark the current node as visited and enqueue it
        State<T> curr = s->getInitialState();
        visited.push_back(curr);
        myQueue.push(curr);
        // vertices of a vertex
        while(!myQueue.empty())
        {
            // Dequeue a vertex from queue and print it
            curr = myQueue.front();
            myQueue.pop_front();
            list<State<T>> adj = s->getAllPossibleStates(curr);
            // Get all adjacent vertices of the dequeued
            // vertex s. If a adjacent has not been visited,
            // then mark it visited and enqueue it
            // 'i' will be used to get all adjacent
            list<int>::iterator i;
            for (i = adj[s].begin(); i != adj[s].end(); ++i)
            {
                if (!visited[*i])
                {
                    visited[*i] = true;
                    myQueue.push_back(*i);
                }
            }
        }
    }
};


#endif //PROJECT_BFS_H
