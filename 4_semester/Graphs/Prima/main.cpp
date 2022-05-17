#include "graph.h"
int main() {
    srand(time(NULL));
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
    graph G(V);
    G.Prima();
}
