ifndef ASD_LAB6_GRAPH_H
#define ASD_LAB6_GRAPH_H
#include "vector"
#include "iostream"
#include "algorithm"
#define MIN  1000;
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
        vector<vector<int>> g;
        vector <int> visited;
        bool find (int x)
        {
            for (int i = 0; i < visited.size(); i++)
            {
                if(visited[i] == x) return true;
            }
            return false;
        }
    public:
        graph(vector<vector<int>> g)
        {
            this->g = g;
            int index = rand()%g.size(); //Cлучайным образом генерируем вершину, с которой начнем формировать оставное дерево
            visited.push_back(index);
        }

        int FindMinAdj(int vertex)
        {
            int min = MIN;
            int vertexMin = -1;
            for (int i = 0; i < g.size(); i++)
            {
                if(g[vertex][i] < min && g[vertex][i] > 0 && !find(i))
                {
                    min = g[vertex][i];
                    vertexMin = i;
                }
            }
            return vertexMin; //Если возращаемое значение -1, то вершина не имеет соседей среди непосещенных
        }

        void Prima()
        {
            if(visited.empty())
            {
                int index = rand()%g.size(); //Cлучайным образом генерируем вершину, с которой начнем формировать оставное дерево
                visited.push_back(index);
            }
            vector <Edge> tree; // Хранит ребра оставного дерева
            int totalWeight = 0;
            while(tree.size() != g.size()-1) //Остовное дерево всегда имеет на 1 ребро меньше, чем кол-во вершин
            {
              int eWeight = MIN; int eNode_2 = -1; int eNode_1 = -1; // Контрольные значения для сравнения
              for (const int &vertex : visited)
               {
                   int m = FindMinAdj(vertex); // Для каждой из посещенных вершин находим непосещенную с минимальным расстоянием
                   if(g[vertex][m] < eWeight && m!= -1)
                   {
                       eNode_2 = m;
                       eWeight = g[vertex][eNode_2];
                       eNode_1 = vertex;
                   }
               }
               Edge e(eNode_1,eNode_2,eWeight);
               cout << e.node_1 << "<-->" << e.node_2 << "; w = " <<e.weight <<"\n";
               visited.push_back(e.node_2);
               tree.push_back(e);
               totalWeight += eWeight;
            }
            cout << "Минимальный вес оставного дерева = " << totalWeight;
            visited.clear();
        }
};

#endif //ASD_LAB6_GRAPH_H
