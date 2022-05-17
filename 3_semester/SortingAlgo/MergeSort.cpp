#include <iostream>
using namespace std;

// Вспомогательные функции для обратки пользовательского ввода:
void   PrintArray ( int arr [], int size) {
    for ( int i = 0 ; i <size; i ++) {
        cout << arr [i] << "  " ;
    }
}
void   FillArray ( int arr [], int size) {
    for ( int i = 0 ; i <size; i ++) {
        cout << " Введите " << i + 1 << " массива элемента " ;
        cin >> arr [i];
    }
}
//Функция Merge:
//1.Создать копии подмассивов  First <- Arr[start1 ... middle] Second <- Arr[middle+1 ... end2]
//2.Создать три указателя:
//-firstStart поддерживает текущий индекс First, начиная с 0
//-secondStart поддерживает текущий индекс Second, начиная с 0
//-current поддерживает текущий индекс Arr [start..end], начиная с p
//3.Пока мы не достигнем конца First или Second, выберите больший из элементов из First и Second и поместите их в правильное положение в Arr [start..end]
//4.Когда у нас кончаются элементы в First или Second, возьмите оставшиеся элементы и поместите в Arr [start...end]
void Merge(int Arr[],int start1, int middle, int end2)
{
    //Cоздадим копии массивов First <- Arr[start1 ... middle] Second <- Arr[middle+1 ... end2]
    int nFirst = middle - start1 + 1;
    int nSecond =  end2 - middle;
    int First[nFirst]; int Second[nSecond];
    for (int i = 0; i < nFirst; i++)//Копируем элементы в First
        First[i] = Arr[start1 + i];
    for (int j = 0; j < nSecond; j++)//Копируем элементы в Second
        Second[j] = Arr[middle + 1 + j];

    //Создаем три указателя:
    int iFirst = 0; int iSecond = 0; int current = start1;
    //Cлияние в правильном порядке
    while(iFirst < nFirst && iSecond < nSecond) { //Пока мы не достигнем конца First или Second, выберите больший из элементов из First и Second и поместите их в правильное положение в Arr [start1..end2]
        if(First[iFirst] < Second[iSecond]) {
            Arr[current] = First[iFirst];
            iFirst++;
        }
        else {
            Arr[current] = Second[iSecond];
            iSecond++;

        }
        current++;
    }
    while(iFirst < nFirst) {//Когда у нас кончаются элементы в Second, возьмите оставшиеся элементы и поместите в Arr [start...end]

        Arr[current] = First[iFirst];
        current++;
        iFirst++;
    }
    while(iSecond < nSecond) {//Когда у нас кончаются элементы в First, возьмите оставшиеся элементы и поместите в Arr [start...end]
        Arr[current] = Second[iSecond];
        current++;
        iSecond++;
    }
}
//Алгоритм сортировки слиянием можно описать концепцией "разделяй и властвуй".
//"Разделяй" мы делим входящую подпоследовательность на две подпоследовательности, до тех пор, пока получившаеся подпоследовательность имеет размер больше 1 элемента.
//Когда подпоследовательность состоит лишь из одного элемента, мы должны отсортировать каждый из получившихся подмассивов - этап "Властвуй".
//Когда мы отсортировали каждый из получившихся массивов, мы комбинируем их.

//Cведения об алгоритме:
//сложность О(n*logn)
//требуется дополнительная память по объему равной объему сортируемого файла
void MergeSort(int Arr[],int start, int end) {
    if (start >= end) return; // БАЗА РЕКУРСИИ
    //РЕКУРСИВНЫЙ СЛУЧАЙ:
    int middle = (start+end)/2;
    MergeSort(Arr, start, middle);
    MergeSort(Arr, middle+1, end);
    Merge(Arr, start, middle, end);

}
int main() {
    int size;
    cout << "Введите количество элеменнтов в массиве ";
    cin >> size;
    int arr[size];
    FillArray(arr,size);
    MergeSort(arr,0,size-1);
    cout << "Отсортированный массив: ";
    PrintArray(arr, size);
    return 0;
}
