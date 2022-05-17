#include <iostream>
#include <cmath>
using namespace std;
//Вспомогательные функции для обратки пользовательского ввода:

void  PrintArray ( int arr[],int size) {
    for(int i = 0; i < size;i++) {
        cout << arr[i] << " ";
    }
}
void  FillArray ( int arr [], int size) {
    for ( int i = 0 ; i < size; i++) {
        cout << " Введите " << i + 1 << " массива элемента " ;
        cin >> arr [i];
    }
}

//Вспомогательные функции для СountingSort, RadixSort:

int GetRank(int number){
    int rank = 1;
    while (number / 10 > 0) {
        number = number / 10;
        rank++;
    }
    return rank;
}
int GetDigit(int number, int position)
{
    if(GetRank(number) < position) return 0;
    int a = pow(10,position);//число, степень 10, равная разряду, который мы хотим получить, т.е. 2769, мы хотим получить разряд тысячных, значит a =1000;
    int b = pow(10,position-1); //число, на которое мы делим остаток от деления, равный number%a
    return number % a/b;
}
int GetMin(int arr[],int size,int position) {
    int min = 10;
    for(int i = 0; i < size; i++) {
        int digit = GetDigit(arr[i],position);
        if(digit < min) min = digit;
    }
    return min;
}
int GetMax(int arr[],int size,int position) {
    int max = 0;
    for(int i = 0; i < size; i++) {
        int digit = GetDigit(arr[i],position);
        if(digit > max) max = digit;
    }
    return max;
}
int GetMaxRank(int arr[], int size) {
    int Maxrank = 1;
    for(int i = 0; i < size; i++) {
        int rank = GetRank(arr[i]);
        if(rank > Maxrank) Maxrank = rank;
    }
    return Maxrank;
}

//СОРТИРОВКА ПОДСЧЕТОМ ПО КЛЮЧУ(разряд числа). Принимает:массив, размер массива(size) и разряд, по которому будут отсортированы числа. Алгоритм:
//1)найти минимальный элемент последовательности в указанном разряде: GetMin
//2)найти максимальный элемент последовательности в указанном разряде: GetMax
//3)завести массив support,длинной max-min+1,заполним ее 0
//4)Выполняем проход по сортируемой последовательности: Пусть текущий элемент = 5, min = -2, max =7
    //4.1)Из элемента мы вычитаем значение минимума 5-(-2)=7. Значит support[7]+=1 и т.п.
//5)Совершаем обратный проход по массиву support и заполняем его значениями: sSize-=support[i]; support[i] = sSize. sSize = размеру массива
//6)Объявляем массив sortedArr[size] = {0}
//7)Заполняем массив sortedArr:
   //7.1)sortedArr[support[GetDigit(arr[i],position)-min]] = arr[i];
    //7.2)support[GetDigit(arr[i],position)-min] +=1;
//8) С помощью цикла от 0 до size присваиваем arr[i] = sortedArr[i] (по указателю на arr[i]
// Таким образом,массив arr отсортируется по одному из разрядов

void CountingSort(int arr[],int size,int position) {
    int min = GetMin(arr,size,position); //нашли минимальный элемент последовательности
    int max = GetMax(arr,size,position);//нашли максиммальный элемент последовательности
    int supportSize = max-min+1; //размер вспомогательного массива
    int support[supportSize] = {0};
    for(int i = 0; i < size; i++) { // cм п.4), п.4.1)
        int supportIndex = 0;
        supportIndex = GetDigit(arr[i],position)-min;
        support[supportIndex]+=1;
    }
    int sSize=size;//Переменная в которой храним размер входящего массива
    for(int i = supportSize-1; i>=0; i--)//обратный проход по массиву support
    {
        sSize -= support[i];
        support[i] = sSize;
    }
    int sortedArr[size];//6)
    for(int i = 0; i < size; i++) //cм. п.7), п.7.1) , п. 7.2)
    {
        sortedArr[support[GetDigit(arr[i],position)-min]] = arr[i];
        support[GetDigit(arr[i],position)-min] +=1;
    }

    for(int i = 0;i < size;i++){ //С помощью цикла от 0 до size присваиваем arr[i] = sortedArr[i] (по указателю на arr[i]
        int *ptrArr = &arr[i];
        *ptrArr = sortedArr[i];
    }
}

//Поразярдная сортировка(корневая сортировка) ИДЕЯ: сортировкой подсчетом  остортировать входной массив по последнему разряду, по предпоследнему и т.д.
// Первый шаг: узнать максимальное количество разрядов числа, входящего в массив: GetMaxRank
//Второй шаг: в цикле от 1 до maxRank = GetMaxRank(arr,size) вызывать функцию сортировки подсчетом: CountingSort

void RadixSort(int arr[], int size)
{
    int MaxRank = GetMaxRank(arr,size);
    int position = 1;
    for(position = 1; position <= MaxRank; position++) {
        CountingSort(arr,size, position);
    }
}

int main() {
    int size;
    cout << "Введите количество элеменнтов в массиве ";
    cin >> size;
    int arr[size];
    FillArray(arr,size);
    RadixSort(arr,size);
    cout << "Отсортированный массив: ";
    PrintArray(arr, size);
    return 0;
}
