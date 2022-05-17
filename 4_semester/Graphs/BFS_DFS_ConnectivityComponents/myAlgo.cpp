#include "queue"
#include "list"
#include <iostream>
#include <vector>
bool find_Q(std::queue<int> Q, int x) {
    while(!Q.empty()) {
        if(Q.front() == x) return true;
        Q.pop();
    }
    return false;
}
bool find_L(std::list<int> L, int x)
{
    while(!L.empty())
    {
        if(L.front() == x) return true;
        L.pop_front();
    }
    return false;
}
