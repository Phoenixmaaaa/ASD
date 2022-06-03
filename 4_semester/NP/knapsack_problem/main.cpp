#include <iostream>
#include <vector>
#include "string"
#define N 3 // Количество вещей
using namespace std;
struct thing
{
    string name;
    int weight, price;
    thing(string  name,int weight, int price): name(name), weight(weight), price(price) {}
};

 int CountMaxPrice(thing T [N], int maxCapacity) // Возвращает максимальную стоимость вещей, которые можно получить в рюкзак вместимости maxCapacity
{
    int arr[N+1][maxCapacity+1]; // таблица с местом для ячеек пустышек
    for (int i = 0; i <= N; i++) // Проходим по всем вещам
    {
        for (int j = 0; j <= maxCapacity; j++) // Проходим по всем "малым" рюкзакам
        {
            // Попали в пустышку
            if (i == 0 || j == 0) {
                arr[i][j] = 0;
            }
                // Попали в рюкзак
            else {
                if (T[i - 1].weight >
                    j) // если вес текущей вещи больше максимальной вместимости i-го рюзкака
                {
                    arr[i][j] = arr[i - 1][j]; //Берем предыдущую или 0
                } else {
                    int prev = arr[i - 1][j]; // Значение над текущей ячейкой

                    int byFormula = T[i - 1].price + arr[i - 1][j - T[i -1].weight]; // Стоимость текущей вещи + стоимость оставшегося места:
                    // ячейка[i-1][вместимость рюкзака - вес текущей вещи];
                    arr[i][j] = max(prev, byFormula);

                }

            }
        }
    }
    int W[maxCapacity]; // Все мои маленькие рюкзаки
    for (int i = 0; i <= maxCapacity; i++) W[i] = i;
    int k = N; int s = maxCapacity;
    while(arr[k][s]!= 0)
    {
        if (arr[k - 1][s] != arr[k][s])
        {
            cout << T[k-1].name << ": вес " << T[k-1].weight << "ед., цена: " << T[k-1].price << "\n";
            k = k - 1;
            s = s - W[k];
        }
        else
        {
            k = k -1;
            s = s;
        }
    }
    return arr[N][maxCapacity];
}

int main()
{
     // Набор вещей
    thing thing_1("Ожерелье",4,4000);
    thing thing_2("Кольцо",1,2500);
    thing thing_3("Подвеска",3,2000);

    thing T[N] = { thing_1,thing_2,thing_3};
    int maxCapacity = 4;
    int maxPrice = CountMaxPrice(T,maxCapacity);
    cout << "Максимальная стоимость товаров = " << maxPrice << " для рюказка вместимости " << maxCapacity << "ед.";
}
