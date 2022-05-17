#include <iostream>
#include <string>
#include <fstream>
#include "HashTab.h"
#define pwd "/home/marusia/CLionProjects/HashTable14/"
#define pathToOut "/home/marusia/CLionProjects/HashTable14/out"
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
