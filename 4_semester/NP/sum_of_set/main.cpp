#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> set = {5, -7, 7, 3, -4}; // Исходное множество
    int max_sum = INT8_MAX; // Максимальное значение
    vector<int> resultSet; // Будущее подмножество суммы 0
    for(int index = 0; index < set.size(); index++)
    {
        vector<int> middelSet; // Промежуточное подмножество
        int sum = set[index];
        middelSet.push_back(sum);
        for(int i = 0; i < set.size(); i++) // Для всех элементов исходного множества, кроме index
        {
            if(i==index) continue;
            if(abs(sum + set[i]) < abs(sum)) // Если модуль суммы sum и текущего элемента исходного множества меньше sum,
            {
                sum += set[i];
                middelSet.push_back(set[i]);   // то полагаем, что этот элемент надо включить
            }
        }
        if(sum == 0) // Нашли хотя бы одно промежуточное подмножество, этого достаточно
        {
            resultSet = middelSet;
            break;
        }
        if(sum < max_sum )
        {
            resultSet = middelSet;
            max_sum = sum;
        }
    }

    for(auto s: resultSet) // Вывод всех элементов множества
    {
        cout << s << " ";
    }
}

