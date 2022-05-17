#ifndef ASD_LAB1_GRAPH_H
#define ASD_LAB1_GRAPH_H
#include "myAlgo.cpp"
using namespace std;

class graph
{
private:
    int size;
    vector<vector<int>> g;
    vector<bool> visitedNodes;

 int GetUnvisitedNode()
 {
     for (int i = 0; i < this->size;i++)
     {
         if(!visitedNodes[i]) {
             return i;
         }
     }
     return -1;
 }

public:
    graph(int size, vector<vector<int>> g)
    {
        this->size = size;
        this->g = g;
        this->visitedNodes = vector<bool>(size, false);

    }
    void printGraph ()
    {
        for (int i  = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << g[i][j]<< " ";
            }
            cout << "\n";
        }
    }
    vector<int> GetAdjacentNodes (int node)
    {
        vector<int>AdjNodes;
        for (int i = 0; i < size; i++)
        {
            if (g[node][i] != 0) {
                AdjNodes.push_back(i);
            }
        }
        return AdjNodes;
    }
    void BFS (int startPos)
    {
     // Шаг 0:
        queue<int> q; // Очередь, где будут находится все встречаемые нами вершины
        int distanse[this->size]; // Массив расстояний от стартовой вершины до всех остальных
        for(int i = 0; i < this->size; i++)
        {
            distanse[i] = -1;
        }
        q.push(startPos); // Помещаем стартовую в очередь
        distanse[startPos] = 0; // Обновляем расстояние до самой себя, равно = 0;
      //Шаг 1 и последующие
        while (!q.empty()) // Пока очередь не пуста
        {
            int curNode = q.front(); // Извлекаем вершину в начале очереди
            q.pop(); // удаляем
            visitedNodes[curNode] = true; // обновляем посещения
            vector <int> AdjNodes = GetAdjacentNodes(curNode); // Получаем соседей
            for (int i = 0; i < AdjNodes.size();i++) // Для каждого из полученных соседей
            {
                if(!find_Q(q,AdjNodes[i]) && !visitedNodes[AdjNodes[i]]) { // Нет ли нашего соседа в очереди или в посещенных
                    q.push(AdjNodes[i]); // Помещаем в очередь, если условие верно
                    distanse[AdjNodes[i]] = distanse[curNode]+1; // обновляем расстояния
                }
            }
        }
        //Таким образом массив distance содержит кратчайшие расстояния от стартовой вершины до всех остальных. Печатаем их.
        cout << "\nРасстояние расчитаны от стартовой вершины = " << startPos << "\n";
        cout << "Вершина    ";
        for (int i = 0; i < this->size; i++)
        {
            cout << i << "|";
        }
        cout << "\nРасстояния ";
        for (int i = 0; i < this->size; i++)
        {
            if(distanse[i] > -1)
                cout << distanse[i] << "|";
            else
                cout << "x" << "|";
        }
    } // Алгоритм обхода графа в ширину и поиска кратчайших путей.

    void FindConnectivityCompopnentByBFS()
    {
        int cntComponent = 0; // Количество компонент связности графа
        while (GetUnvisitedNode() > -1)
        {
            BFS(GetUnvisitedNode()); // Получаем первую попавшуюся непосещенную и для нее BFS
            cntComponent++;
        }
        this->visitedNodes = vector<bool>(size, false);
        cout << "\nКоличество компонент связности графа = " << cntComponent;
    } // Алгоритм подсчета компонентов связности, c помощью BFS

    void recursiveDFS(int startPos)
    {
        cout << startPos  << " ";
        visitedNodes[startPos]=true;
        for (int i=0; i<=size; i++)
            if ((g[startPos][i]!=0) && (!visitedNodes[i])) // База рекурсии
                recursiveDFS(i);
    } //Рекурсивный обход в глубину

    void FindConnectivityCompopnentByDFS()
    {
        int cntComponent = 0; // Количество компонент связности графа
        while (GetUnvisitedNode() > -1) //  Пока у нас не все вершины в графе,отмечены как посещенные
        {
            cout << "Компонента связности №" << cntComponent+1 << ": ";
            recursiveDFS(GetUnvisitedNode()); //Получаем первую попавшуюся непосещенную
            cntComponent++;
            cout << "\n";
        }
        this->visitedNodes = vector<bool>(size, false);
        cout << "Количество компонент связности графа = " << cntComponent;
    } // Алгоритм подсчета компонентов связности, c помощью DFS

    vector<vector<int>> GetReachabilityMatrix() // Получаем матрицу достижимости графа, используя иттеративный DFS
    {
        vector<vector<int>> reachabilityMatrix(size, vector<int>(size, 0)); // Будущая матрица достижимости
         for(int i = 0; i < this->size; i++)  // Для каждой вершины,иттеративный DFS
         {
             list<int> stack; // CД FIFO
             vector<int> Adj_i; // Массив достижимых соседей для текущей верщины i
             stack.push_front(i); // Помещаем текущую вершину i в стэк
             Adj_i.push_back(i);// Каждая вершина достижима сама для себя
             visitedNodes[i] = true; // Отмечаем ее как посещенную вершину
             while (!stack.empty()) // Пока стэк не пуст
             {
                 int curNode = stack.front(); // Снимаем с вершины стэыка вершину curNode графа
                 stack.pop_front(); // Удаляем ее из графа
                 visitedNodes[curNode] = true; // Отмечаем посещенной
                 vector <int> AdjNodes = GetAdjacentNodes(curNode); // Для curNode ищем соседей
                 for (int j = 0; j < AdjNodes.size(); j++) // Для каждого соседа curNode
                 {
                     if (!visitedNodes[AdjNodes[j]]) // Если сосед curNode не посещен еще
                     {
                         if (find_L(stack, AdjNodes[j])) { // Но сосед curNode уже в стэке
                             stack.remove(AdjNodes[j]); // Удаляеи из стэка и затем продвинем ее к вершине
                         }
                         stack.push_front(AdjNodes[j]); // Добавляем в стэк
                         Adj_i.push_back(AdjNodes[j]); // добавляем в достижмые соседи для нашей вершины i
                     }
                 }
             }
             // Затем масссив Adj_i содержит все достижмые из i вершины. Заполняем матрицу достижимсоти
             for (int k: Adj_i)
             {
                 reachabilityMatrix[i][k] = 1;
             }
             visitedNodes = vector<bool>(size, false);
         }
        return reachabilityMatrix;
    }
    vector <vector<int>> GetProductMatrix (vector<vector<int>> reachMatrix)
    {
        vector<vector<int>> M(this->size,vector<int>(this->size,0));
        for (int i = 0; i < this->size; i++)
        {
            for (int j = 0; j < this->size; j++)
            {
                M[i][j] = reachMatrix[j][i]*reachMatrix[i][j];
            }
        }
        return M;
    }

    void FindStrongComponents()
    {
      vector<vector<int>> components;
      vector<vector<int>> reachMatrix = GetReachabilityMatrix(); // Вычисляем матрицу достижимости
      vector<vector<int>> M = GetProductMatrix(reachMatrix); // Поэлементное произведение (reachMatrix)^T * reachMatrix;
      // В итоге мы получим матрицу у которой некоторые строки будут одинаковыми, они и формируют сильные компоненты связности
      for (int i = 0; i < this->size; i++)
      {
          if(visitedNodes[i])
              continue;
          visitedNodes[i] = true;
          vector <int> component_i;
          component_i = vector<int>(1,i);
          for(int j = i+1; j < this->size; j++)
          {
              if(M[i] == M[j])
              {
                  visitedNodes[j] = true;
                  component_i.push_back(j);
              }
          }
          components.push_back(component_i);
      }
        visitedNodes = vector<bool>(size, false);
      // Печать компонентов сильной связности
        cout << "Количество сильных компонентов связности графа = " << components.size() << "\n";
        for (int i = 0; i < components.size(); i++)
        {
            cout << "Cильная компонента № "<< i+1 << ": ";
            auto component = components[i];
            for(int node: component)
            {
                cout << node << " ";
            }
            cout << "\n";
        }
    } // Поиск сильных компонент связности
};


#endif //ASD_LAB1_GRAPH_H
