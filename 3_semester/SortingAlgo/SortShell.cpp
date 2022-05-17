#include <iostream>
using namespace std;

//Сортировка Шелла, это улучшенный алогоритм сортировки простыми вставками.
//Мы сравниваем эелменты, стоящие на определенном расстояние друг от друга, затем мы уменьшаем это расстояние пока оно не станет равно 1
//В худшем случае, если использовать, длину промежутка равную N/2 с шагом step /=2, то сложность алгоритма О(N^2)
//Преимущества: внутреняя сортировка


void FillArray(int arr[], int size) {
    for(int i = 0; i < size; i++){
        cout << "Введите " << i+1 <<" элемент массива ";
        cin >> arr[i];
    }
}

void PrintArray(int arr[], int size) {
    for(int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}

void ShellSort(int arr[],int size) {
    int i,j, step, current;
    for(step = size/2; step > 0; step /=2) {//Основной цикл бежит по "шагу" в сортировке Шелла. Например, для массива из 10 элементов шаги будут: 5 2 1
       for(i = step; i <size; i++) {
           current = arr[i];
           for(j = i; j >= step; j -=step) {// цикл бежит от элемента arr[step] до конца массива и сранивает arr[step] c arr[j-step]
               if(current < arr[j-step]) {
                   arr[j] = arr[j-step];
               }
               else
                   break;
           }
           arr[j] = current;
       }
    }
}

int main() {
    int size;
    cout << "Введите количество элеменнтов в массиве ";
    cin >> size;
    int arr[size];
    FillArray(arr,size);
    ShellSort(arr,size);
    PrintArray(arr, size);
    return 0;
}
