#ifndef ASD_LAB5_GRAPH_H
#define ASD_LAB5_GRAPH_H
#include "vector"
#include "iostream"
#include<algorithm>
using namespace std;

struct Edge
{
    int node_1;
    int node_2;
    int weight;
    Edge(int node_1, int node_2, int weight)
    {
        this->node_1 = node_1;
        this->node_2 = node_2;
        this->weight = weight;
    }

};
class graph
{
    private:
        vector <Edge> g;
        int amountVertex;
    public:
        graph (vector <Edge> graph,int amountVertex)
        {
            this->g = graph;
            for(int i = 0; i < g.size(); i++)
            {
                root.push_back(i);
            }
            this->amountVertex = amountVertex;
        }
        void Bellman_Ford(int startV)
        {
        // Шаг 0
           vector <int> distanse;
           for (int i = 0; i < amountVertex; i++)
           {
               if(i!=startV)
                   distanse.push_back(INT8_MAX);
               else
                   distanse.push_back(0);
           }
           // Шаг 1 .. n-1
           for (const Edge &e : g)
           {
               if(distanse[e.node_2] > distanse[e.node_1]+e.weight)
               {
                   distanse[e.node_2] = distanse[e.node_1]+e.weight; // Релаксируем ребро e
               }
           }
           // Шаг n : проверка критерия сущестования цикла отрицательной длины
            for (const Edge &e : g)
            {
                if(distanse[e.node_2] > distanse[e.node_1]+e.weight)
                {
                    cout << "Граф содержит цикл отрицательной длины";
                    return;
                }
            }
            // Печать расстояний
            cout << "Кратчайшие расстояния:\n";
            for (int i = 0; i < distanse.size(); i++)
            {
                if(i == startV) continue;
                cout << startV << "<-->" << i << " = ";
                if (distanse[i] > 0)
                    cout <<"+" <<distanse[i] <<"\n";
                else
                    cout <<distanse[i] << "\n";
            }
        }
};
#endif //ASD_LAB5_GRAPH_H
