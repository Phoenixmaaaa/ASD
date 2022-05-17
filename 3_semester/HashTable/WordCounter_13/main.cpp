#include <iostream>
#include <string>
#include <fstream>
#include "HashTab.h"
#define pwd "/home/marusia/CLionProjects/HashTable13/"
#define pathToOut "/home/marusia/CLionProjects/HashTable13/out"
using namespace std;


int main() {
    string nameOfFile;
    cout << "Введите путь до файла, который необходимо занести в таблицу\n";
    cin >> nameOfFile;
    string pathToText = pwd+nameOfFile;
    ifstream in (pathToText); ofstream out(pathToOut);
    HashTab Table;
    string result;
    while(in >> result){
        Table.Add(result);
    }
    out << Table.Print();
    out.close(); in.close();
    return 0;
}
/* Пример входных данных:

My name Masha word like word super apple banana lalalalala apple Masha My My name word like 

Пример выходных данных:

My 3
name 2
Masha 2
word 3
like 2
super 1
apple 2
banana 1
lalalalala 1
*/
