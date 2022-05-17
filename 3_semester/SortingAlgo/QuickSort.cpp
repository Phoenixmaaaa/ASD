#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
//Вспомогательные функции для обработки пользовательского ввода
void  PrintVector ( vector<int> v) {
    for(int i =0; i < v.size();i++) {
        cout<< v.at(i) << " ";
    }
}
void FillVector(vector<int>&arr, int size) {
    for(int i = 0; i < size; i++) {
        int x; cout << i+1 << " элемент ";
        cin >> x;
        arr.push_back(x);
    }
}
//Функция для слияния векторов Less, в котором хранятся элементы <= pivot, pivot и вектора Greater, в котором харнятся значение больше pivot;
vector<int> MergeSortedVectors(vector<int> Less, int pivot, vector<int> Greater) {
    vector<int> result;
    for(int i = 0; i < Less.size(); i++) {
        result.push_back(Less.at(i));
    }
    result.push_back(pivot);
    for(int i = 0; i < Greater.size();i++) {
        result.push_back(Greater.at(i));
    }
    return result;
}
//Cведения об алгоритме:
//Cложность О(n*logn)
//Требуется доп.память
void QuickSort(vector <int> &sequence) {
    vector<int> result;
    if (sequence.size()<2) {
        return; // БАЗА РЕКУРСИИ
    }
    //РЕКУРСИВНЫЙ СЛУЧАЙ:
    int index = rand()%sequence.size();//рандомно генерируем индекс опорного элемента
    int pivot = sequence.at(index);//опорный элемент
    vector<int> Less; vector<int> Greater;//Less хранит элементы меньше или равные pivot, Greater хранит элементы больше pivot
    for(int i = 0; i < sequence.size(); i++){
        if(i == index) continue;
        if(sequence.at(i) <= pivot) Less.push_back(sequence.at(i));
        else Greater.push_back(sequence.at(i));
    }
    QuickSort(Less);//Cортируем аналогично вектор Less: выбираем опорный, делим на элементы меньше опорного и больше опорного и т.п.
    QuickSort(Greater);//Сортируем аналогично вектор Greater;
    result = MergeSortedVectors(Less, pivot, Greater);//result - это слияние отсортированных векторов Less+pivot+Greater
    sequence = result;
}
int main() {
    srand(time(NULL));
    vector<int> sequence; int size;
    cout << "Введите количество элементов "; cin >> size;
    FillVector(sequence, size); QuickSort(sequence); PrintVector(sequence);
    return 0;
}
