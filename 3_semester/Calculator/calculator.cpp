// Калькулятор со скобками. https://www.youtube.com/watch?v=Vk-tGND2bfc
#include <iostream>
#include <stack>
#include <strings.h>
#include <math.h>

using namespace std;
//функция с помощью которой мы определяем приоритет операции
int Priority(char c) {
    int priority;
    if (c == '-' || c == '+') priority = 1;
    else if (c == '/' || c == '*') priority = 2;
    else priority = -1;
    return priority;
}
//Базовые операции
float BaseOperation(char c, float f,float s) {
    float result = 0;
    switch (c) {
        case '+':
            result = f + s;
            break;
        case '-':
            result = f-s;
            break;
        case '*':
            result = f * s;
            break;
        case '/':
            result = f / s;
            break;
    }
    return result;
}
//корректно ли расставлены скобки
bool IsCorrecrtBrackets(string x) {
    stack <char> brackets;
    for (int i = 0; i < x.length(); i++) {
        switch (x[i]) {
            case '(':
                brackets.push(x[i]);
                break;
            case ')':
                if (!brackets.empty() && brackets.top() == '(')
                    brackets.pop();
                break;
        }
    }
        if (brackets.empty())
            return true;
        else
            return false;
}

//Переводим строку в число
float toNumber(string multyDigitNumber) {
    int size = multyDigitNumber.size();
    float res = 0;
    int power = 0;
    for(int i = size-1; i>-1; i--) {
        float m = (multyDigitNumber[i] - '0');
        res += m*pow(10,power);
        power++;
    }
    return res;
}
//Скобочный калькулятор
float calculator(string x) {
    //Проверяем верно ли рассталвены скобки
   if(!IsCorrecrtBrackets(x)) {
        throw "Cкобки расставлены неверно";
    }
    stack <float> numbers;//завели стек чисел
    stack <char> Stoperation;//завели стек операций
    bool lastIsDigit = false; //флаг, с помощью которого мы определяем многоразрядные числа
    string multyDiginNumber; //переменная в которой храним многоразрядные числа
    //основная логика
    for (int i = 0; i < x.size(); i++) { // Если текущий символ входной строки - это число, то кладем его в стек с числами
        if (x[i] >= '0' && x[i] <= '9') {
            if(!lastIsDigit){
                numbers.push(x[i]-'0');
                lastIsDigit = true;
                multyDiginNumber=x[i];
            }
            else {
                multyDiginNumber+=x[i];
                numbers.pop();
                numbers.push(toNumber(multyDiginNumber));
                lastIsDigit = true;
            }
        }

        else if (x[i] == '(') { //Добавляем символ открытой скобки в стек с операциями, всегда
            Stoperation.push(x[i]);
            lastIsDigit = false;
        }
        else if (Stoperation.empty() ||  Priority(x[i]) > Priority(Stoperation.top())) { // Если стек операндов пуст или приоритет текущего выше, чем приоритет последнего добавленного,то всегда добавляем в стек операций
            Stoperation.push(x[i]);
            lastIsDigit = false;
        }
        else if (Priority(x[i]) <= Priority(Stoperation.top()) && Priority(x[i]) > 0) { //Если приоритет текущего ниже или равен, чем приоритет последнего добавленного в стек операций, то
            while (!Stoperation.empty() && Priority(x[i]) <= Priority(Stoperation.top())) { // пока выполняется это условие, извлекаем два последних числа,добавленных в стек чисел и последнюю операцию
                float s,f;
                s = numbers.top();
                numbers.pop(); // удаляем последнее число из стека чисел
                f = numbers.top();
                numbers.pop(); // удалаяем "предпоследнее" число из стека чисел
                float M;
                if(Stoperation.top()=='/' && s == 0) { // проверяем исключение деление на 0
                    throw "Деление на 0";
                }
                M = BaseOperation(Stoperation.top(), f, s);
                numbers.push(M);// результат вычислений добалвяем стек чиел
                Stoperation.pop(); // удаляем выполненную операцию
            }

            Stoperation.push(x[i]);
            lastIsDigit = false;
        }
        else if (x[i] == ')') { // Если текущий символ закрытая скобка, то мы должны выполнить, соблюдая приоритет, все действия в скобке, пока не встреим открывающуяся, затем удалить "("
            while (Priority(Stoperation.top() ) > 0 && !Stoperation.empty())
            {
                float s,f;
                    s = numbers.top();
                    numbers.pop();
                    f = numbers.top();
                    numbers.pop();
                    float M;
                    if(Stoperation.top()=='/' && s == 0)
                    {
                        throw "Деление на 0";
                    }
                    M = BaseOperation(Stoperation.top(), f, s);
                    numbers.push(M);
                Stoperation.pop();
            }
           if(Stoperation.top()=='(') Stoperation.pop();
           lastIsDigit = false;
        }
    }
    // Если входная строка полностью разобрана, но стек операций не пуст, то пока стек операций не пуст, достаем последнее и предпоследнее числа из стека чисел и выполянем операции
    if (!Stoperation.empty())
    {
        while (!Stoperation.empty())
        {
            float s,f;
            s = numbers.top();
            numbers.pop();
            f = numbers.top();
            numbers.pop();
            float M;
            if(Stoperation.top()=='/' && s == 0)
            {
                throw "Деление на 0";
            }
            M = BaseOperation(Stoperation.top(), f, s);
            numbers.push(M);
            Stoperation.pop();
        }
    }
    return numbers.top();
}
int main() {
    setlocale(LC_ALL,"ru");
    string x;
    cout << "Введите выражение: ";
    cin >> x;
    float a;
    try {
        a = calculator(x);
        cout << "Результат вычислений: " << a << endl;
    }
    catch( const char *ex) {
        cout << "Ошибка!" << ex << endl;
    }
}

