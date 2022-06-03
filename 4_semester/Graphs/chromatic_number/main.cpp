#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Graph
{
    private:

        vector<vector<int>> g; // граф задается матрицей смежности
        vector <bool> isColored; // Окрашена ли вершина
        vector<pair<int,int>> D; // Массив пар: номер вершины <--> степень вершины

    static bool compare(pair<int,int> p1, pair<int,int> p2) // функция сравнения для отсортировки вершин списка D по неубыванию стеепеней вершин
    {
        return p1.second > p2.second;
    }

    int getDegree(int x) // Получение степени вершины;
    {
        int degree = 0;
        for (int i = 0; i < g.size(); i++)
        {
            if(g[x][i] == 1) degree++;
        }
        return degree;
    }

    int next(int cur) // Возвращает первую по списку D неокрашенную вершину
    {
        for (int i = 0; i < g.size(); i++)
        {
            if(!isColored[D[i].first])
                return D[i].first;
        }
        return -1;
    }

    public:

        Graph(vector<vector<int>> g)
        {
            this->g = g;
            for(int i = 0; i < g.size(); i++)
            {
                isColored.push_back(false); // Изначально все вершины не окрашены
                // Заполнение массива D
                int d = getDegree(i);
                pair<int,int> p(i,d);
                D.push_back(p);
            }
            // Отсортировка массива D по неубыванию
           std::sort(D.begin(),D.end(), compare);
        }

        vector<int> GetAdjacentNodes (int node) // Получаем список соседей всех вершин node
        {
            vector<int>AdjNodes;
            for (int i = 0; i < g.size(); i++)
            {
                if (g[node][i] == 1 && isColored[i])
                {
                    AdjNodes.push_back(i);
                }
            }
            return AdjNodes;
        }

        int Coloring(string colors[]) // // Хроматическое число графа g
        {
            int chromatic_num = 0;
            string color_v[g.size()]; // Массив, который хранит для каждой вершины ее цвет
            for(int i = 0; i < g.size(); i++) // Изначально все вершины не имеют цвета
                color_v[i] = "";
// Инциализируем начальные данные, шаг 0:
            int cur = D[0].first; //Первая вершина, которая имеет наивысшую степень
            int colorNum = 0; // Порядковый номер цвета в массиве colors
//Последующие шаги:
            while (cur != -1)
            {
                isColored[cur] = true; // Отметили как окрашенную текущую выбранную вершину
                color_v[cur] = colors[colorNum]; // Дали конкретный цвет вершине сur из массива colors
                cout << "Окрасили в цвет " << color_v[cur] << " вершины: "<< cur << " ";
                for(int i = cur; i < D.size(); i++) // Для всех вершин массива D
                {
                    if(isColored[D[i].first] || g[cur][D[i].first] == 1) continue; // окрашенные и смежные вершины мы пропускаем
                    vector <int> adj = GetAdjacentNodes(D[i].first);// Смотрим ОКРАШЕННЫЕ вершины СМЕЖНЫЕ с нашей вершиной D[i].first ( i - вершина не смежная с cur)
                    bool flag_same_color = false; // Пологаем: Смежная вершина с i имеет НЕ тот же цвет, что  и текущая
                    for (int j = 0; j < adj.size(); j++) // Проверка предположения
                    {
                        if (color_v[adj[j]] == color_v[cur]) // Цвет соседа D[i] совпал с цветом текущим - пропускам D[i]
                        {
                            cout << adj[j] << "<--->"<< color_v[adj[j]]  << "\n";
                            flag_same_color = true;
                            break;
                        }
                    }
                    if(!flag_same_color)
                    {
                        // Окрашиваем вершину i в один цвет с текущей вершиной
                        isColored[D[i].first] = true;
                        color_v[D[i].first]= color_v[cur];
                        cout << D[i].first << " ";
                    }
                }
                chromatic_num++;
                cout << "\n";
                colorNum++;
                cur = next(cur);
            }
            return chromatic_num;
        }
};

int main()
{
    //Создание графа
    int size;
    cout << "Введите количество вершин \n";
    cin >> size;
    vector<vector<int>> V(size, vector<int>(size, 0));
    cout << "Введите матрицу (" << size << "x" << size << ")\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> V[i][j];
        }
    }
    string colors[5] = {"синий", "зеленый", "красный","желтый", "фиолетовый"};
    Graph G (V);
    int n = G.Coloring(colors);
    cout << "Хроматическое число графа = " << n;
    return 0;
    /*

0 1 1 1 0
1 0 1 1 1
1 1 0 0 1
1 1 0 0 1
0 1 1 1 0


 */
}

