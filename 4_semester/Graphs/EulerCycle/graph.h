#ifndef ASD_LAB9_GRAPH_H
#define ASD_LAB9_GRAPH_H
#include <iostream>
#include <vector>
#include "stack"
#include <algorithm>
using namespace std;
class graph
{
private:
    vector<vector<int>> g;
public:
    graph(vector<vector<int>> g)
    {
        this->g = g;
    }
    bool isEulerGraph()
    {
        for (int i = 0; i < g.size(); i++)
        {
            if(GetDegree(i) % 2 == 1)
                return false;
        }
        return true;
    }
    int GetDegree(int x)
    {
        int degree = 0;
        for (int i = 0; i < g.size(); i++)
        {
            if(g[x][i] == 1) degree++;
        }
        return degree;
    }
    int GetAdjV(int x)
    {
        for (int i = 0; i < g.size(); i++)
        {
            if(g[x][i] == 1)
            {
                return i;
            }
        }
        return -1;
    }
    void FindEulerCycle()
    {
        if(!isEulerGraph())
        {
            cout << "Граф не содержит эйлеров цикл\n";
            return;
        }
        stack <int> st;
        vector <int> res;
        st.push(0);
        while(!st.empty())
        {
            int cur_v = st.top();
            int v_Adj = GetAdjV(cur_v);
            if(v_Adj != -1)
            {
                st.push(v_Adj);
                g[cur_v][v_Adj] = g[v_Adj][cur_v] = 0;
            }
            else
            {
                while (GetAdjV(st.top()) == -1)
                {
                    res.push_back(st.top());
                    st.pop();
                    if(st.empty()) break;
                }
            }
        }
        cout << "Эйлеров цикл:\n";
        for (int i = 0; i < res.size(); i++)
        {
            cout << res[i] << " ";
        }
    }

};
#endif //ASD_LAB9_GRAPH_H
