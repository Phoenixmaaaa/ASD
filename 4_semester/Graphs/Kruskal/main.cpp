#include "graph.h"
int main()
{
    int amountVertex; int amountEdge;
    cout << " Введите количество вершин графа ";
    cin >> amountVertex;
    cout << " Введите количество ребер графа ";
    cin >> amountEdge;
    vector <Edge> edges; // Массив отрезков
    for (int i = 0; i < amountEdge; i++)
    {
        int node_1; int node_2; int weight;
        cin >> node_1 >> node_2 >> weight;
        Edge e (node_1,node_2,weight);
        edges.push_back(e);
    }
    graph G(edges,amountVertex);
    G.Kruskal();
   return 0;
}
