#include "graph.h"

void Lab1(graph G, int startPos)
{
    cout << "Лабораторная работа №1" << "\n";
    G.BFS(startPos);
}
void Lab2(graph G)
{
    cout << "Лабораторная работа №2" << "\n";
    G.FindConnectivityCompopnentByBFS();
}
void Lab3(graph G)
{
    cout << "Лабораторная работа №3" << "\n";
    G.FindConnectivityCompopnentByDFS();
}
void Lab4 (graph G)
{
    cout << "\nЛабораторная работа №4" << "\n";
    G.FindStrongComponents();
}

  int main () 
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
      graph G(size, V);
      Lab4(G);
  }
