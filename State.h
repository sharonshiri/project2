#ifndef PROJECT_STATE_H
#define PROJECT_STATE_H

template <class T>
class State {
    T myState;
    double cost;
    State<T>* cameFrom = nullptr; // the state we came from to this state (setter)
public:
    State(){}
    State(T s, double cost) {
        this->myState = s;
        this->cost = cost;
    }
    bool operator==(State<T> s) // we overload Object's < method
    {
     return ((this->cost == s.cost) && (myState == s.myState));
    }
    bool operator<(State<T> s) // we overload Object's < method
    {
        return this->cost < s.cost;
    }
    bool operator>(State<T> s) // we overload Object's > method
    {
        return this->cost > s.cost;
    }
    void setCameFrom(State<T>* s) {
        cameFrom =s;
    }
    State<T>* getCameFrom() {
        return cameFrom;
    }
    T getLoc() {
        return myState;
    }
    double getCost() {
        return cost;
    }

};


#endif //PROJECT_STATE_H