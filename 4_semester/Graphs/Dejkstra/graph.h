#ifndef ASD_LAB7_GRAPH_H
#define ASD_LAB7_GRAPH_H
#include <iostream>
#include "vector"
#include "algorithm"
using namespace std;

class graph
{
    private:
        vector<vector<int>> g;
        vector<bool> L_const;
     int find_min_unvisited(vector <int> V)
     {
         int MIN = INT8_MAX;
         int index;
         for (int i = 0; i < V.size(); i++)
         {
             if(V[i] < MIN && !L_const[i])
             {
                 MIN = V[i];
                 index = i;
             }
         }
         return index;
     }
    public:
    graph(vector<vector<int>> g)
    {
        this->g = g;
        this->L_const = vector<bool>(g.size(), false);
    }
    vector<int> GetAdj(int vertex)
    {
        vector<int> result;
        for(int i = 0; i < g.size(); i++ )
        {
            if(g[vertex][i] > 0 && !L_const[i])
            {
                result.push_back(i);
            }
        }
        return result;
    }
    void Dijkstra(int startV)
    {
        vector <int> L;
        for(int i = 0; i < g.size(); i++)
        {
            if(startV!=i)
            {
                L.push_back(INT8_MAX); // Изначально пометки для всех вершин, кроме стартовой "бесконечность"
            }
            else // Вводим начальные данные о стартовой вершине
            {
                L.push_back(0);
                L_const[startV] = true;
            }
        }
        int current_vertex = startV;
        int steps = 0;
        while (steps != g.size()-1)
        {
            vector <int> AdjVertex = GetAdj(current_vertex);
            for (const int &v : AdjVertex)
            {
                int currentV = L[v]; int possibleV = L[current_vertex]+g[current_vertex][v];
                if(currentV > possibleV)
                {
                    L[v] = possibleV;
                }
            }
            current_vertex = find_min_unvisited(L);
            L_const[current_vertex] = true;
            steps++;
        }
        cout << "Результат работы алгоритма Дейкстры - поиск кратчайших путей в графе:\n";
        for (int i = 0; i < g.size(); i++)
        {
            cout << "Кратчайшее растояние между " <<startV << "<-->" << i <<" = " << L[i] << "\n";
            L_const[i] = false;
        }
        cout << "Количество итераций при алгоритме Дийкстры: " << steps;
    }
};
#endif //ASD_LAB7_GRAPH_H
