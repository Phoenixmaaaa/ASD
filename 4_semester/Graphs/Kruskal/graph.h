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
        vector <int> root;
        int amountVertex;
// Массив root хранит корни вершин.
// Изначально, все вершины считаются независимыми и root: 1,2,3,4 ... size
// Когда возникает зависимость, допустим, между 1 и 2 вершиной, то root: 2,2,3,4...size
// То есть он работает как ссылки: вершина 1 ссылается на 2, а 2 на саму себя, значит у вершин 1,2 общий корень = 2
// Пусть возникла зависимость между 2 и 3 вершиной тогда root: 2,3,3,4...size: вершина 1 ссылается на 2, 2 cсылается на 3, 3 сам на себя, значит 1,2,3 с общим корнем
    static bool compare(Edge a, Edge b)
    {
        return a.weight < b.weight;
    }
    int findRoot (int x)
    {
        if (root[x] == x)
            return x;
        else {
            int root_x = findRoot(root[x]);
            return root_x;
        }
    }
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
        void print ()
        {     for (int i = 0; i < g.size(); i++)
            {
                cout << g[i].node_1 << " " << g[i].node_2 << " " << g[i].weight << "\n";
            }
        }
        void sortEdges()
        {
                std::sort(g.begin(),g.end(), compare);

        }
        void Kruskal ()
        {
            sortEdges(); // Отсортируем ребра по весу по неубыванию
            int weight = 0; int amountEdge = 0;
            for (int i = 0; i < g.size(); i++)
            {
                int rootNode_1 = findRoot(g[i].node_1);
                int rootNode_2 = findRoot(g[i].node_2);
                if(rootNode_1 != rootNode_2)
                {
                    root[rootNode_1] = rootNode_2;
                    weight += g[i].weight;
                    cout << g[i].node_1 << "<-->" << g[i].node_2 << "\n";
                    amountEdge++;

                }
                if(amountEdge == amountVertex-1) break; //  остовное дерево всегда имеет на 1 ребро меньше, чем кол-во вершин

            }
            cout << "Минимальный вес оставного дерева = " << weight;
        }
};
#endif //ASD_LAB5_GRAPH_H

