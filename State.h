#ifndef PROJECT_STATE_H
#define PROJECT_STATE_H

template <class T>
class State {
    T myState;
    double cost;
    // the state we came from to this state
    State<T>* cameFrom= nullptr;
public:
    State(){}
    // func: constructor state
    // * @params T, double - cost
    State(T s, double cost) {
        this->myState = s;
        this->cost = cost;
    }
    // func: operator==
    // @params State<T> other state
    // we overload Object's == method
    bool operator==(State<T> s)
    {
     return ((this->cost == s.cost) && (myState == s.myState));
    }
    // func: operator<
    // @params State<T> other state
    // we overload Object's < method
    bool operator<(const State<T> s) const
    {
        return this->cost < s.cost;
    }
    // func: operator>
    // @params State<T> other state
    // we overload Object's > method
    bool operator>(const State<T> s) const // we overload Object's > method
    {
        return this->cost > s.cost;
    }
    // func: setCameFrom
    // @params State<T>* other state
    // setter to cameFrom
    void setCameFrom(State<T>* s) {
        cameFrom =s;
    }
    // func: getCameFrom
    // @params void
    // getter to cameFrom
    State<T>* getCameFrom() {
        return cameFrom;
    }
    // func: getLoc
    // @params void
    // getter to T
    T getLoc() {
        return myState;
    }
    // func: getCost
    // @params void
    // getter to cost
    double getCost() {
        return cost;
    }
};


#endif //PROJECT_STATE_H