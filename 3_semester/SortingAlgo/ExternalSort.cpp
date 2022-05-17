#include <fstream>
#include <iostream>
using namespace std;
#define pwd "/home/marusia/CLionProjects/ExternalMultyPhaseSort/" // наш pwd
#define pathToA "/home/marusia/CLionProjects/ExternalMultyPhaseSort/A" //путь до вспомогательного файла А
#define pathToB "/home/marusia/CLionProjects/ExternalMultyPhaseSort/B" //путь до вспомогательного файла Б
// функия которая возращает количество чисел в исходном файле
int AmountOfInteger(string path){
    ifstream f(path);
    int cnt; int c;
    while(f >> c) cnt++;
    f.close();
    return cnt;
}
// функция с помощью которой мы ПОПАРНО соединяем отсортированные серии в исходный файл
void Merge(string path, int lenOfSeries,int amountOfInt) {
    ofstream f(path);
    ifstream A(pathToA);
    ifstream B(pathToB);
    int count1 = 0;
    int count2 = 0;
    int a, b;
    bool proc1, proc2;
    if (A >> a) {
        proc1 = true;
    } else proc1 = false;
    if (B >> b) {
        proc2 = true;
    } else proc2 = false;
    for (int i = 0; i < amountOfInt; i += 2 * lenOfSeries) {
        while (count1 < lenOfSeries && count2 < lenOfSeries && proc1 && proc2) {
            if (a < b) {
                f << a << " ";
                if (A >> a) {}
                else proc1 = false;
                count1++;
            } else {
                f << b << " ";
                if (B >> b) {}
                else proc2 = false;
                count2++;
            }
        }
        while (count1 < lenOfSeries && proc1) {
            f << a << " ";
            if (A >> a) {}
            else proc1 = false;
            count1++;
        }
        while (count2 < lenOfSeries && proc2) {
            f << b << " ";
            if (B >> b) {}
            else proc2 = false;
            count2++;
        }
     count1=count2=0;
    }
    A.close(); B.close(); f.close();
}
// функция с помощью которой мы разделяем серии внутри исходного файла на А и В
void SeparationFile(string path,int lenOfSeries){
    ofstream A(pathToA); ofstream B(pathToB); ifstream f(path);
    bool preIsA = false;
    while (!f.eof()) {
        if (!preIsA) {
            for(int i = lenOfSeries; i > 0; i--) {
                int c;
                if(f >> c) {
                    A << c;
                    A << ' ';
                }
            }
            preIsA = true;
        }
        else {
            for(int i = lenOfSeries; i > 0; i--) {
                int c;
                if(f >> c) {
                    B << c;
                    B << ' ';
                };
            }
            preIsA = false;
        }
    }
    A.close(); B.close(); f.close();
}

//ОПИСАНИЕ АЛГОРИТМА ВНЕШНЕЙ СОРТИРОВКИ
/* f - файл,в который записана неотсортированная последовательность.
//А,Б -вспомогательные файлы, в которые записываются серии из f.
Cерия - это отсортированная часть подпоследовательности из f. Изначально количество серий равно количество чисел в f, т.к. последовательность неотсортирвана.
Алгоритм:
Входные данные:
lenOfSeries: 1 - Длина серии изначальная
        amountOfInt: 14 - Количество символов в серии
Если lenofSeries > amountOfInt прервать выполнении функции; в f содержится отсортированная последовательность.
Иначе:
1) Распределяем поочередно по файлам А, Б серии, которые содержаться в f;
2) Попарно сливаем серии в исходный файл f;
3) lenofseries = lenofSeries*2; */
void ExternalSort(string path, int lenOfSeries,int amountOfInt) {
    if(lenOfSeries>amountOfInt) return; //База рекурсии
    SeparationFile(path,lenOfSeries);
    Merge(path, lenOfSeries, amountOfInt);
    lenOfSeries=lenOfSeries*2;
    ExternalSort(path,lenOfSeries,amountOfInt);
}

int main() {
    string nameOfFile;
    cout << "Введите путь до файла, который необходимо отсортировать\n";
    cin >> nameOfFile;
    int amountOfInt = AmountOfInteger(pwd+nameOfFile);
    ExternalSort(pwd + nameOfFile, 1,amountOfInt);
    return 0;
}
