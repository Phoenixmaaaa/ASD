#include <iostream>
#include "BinaryTree.h"
using namespace std;
//Вспомогательные функции для обработки пользовательского ввода
void FillArray(int arr[], int size) {
    for(int i = 0; i < size; i++){
        cout << "Введите " << i+1 <<" элемент массива ";
        cin >> arr[i];
    }
}
void MenuLab17(){
    cout << "Введите линейно-скобочную запись для формирования БНП"<<"\n БНП - это дерево, в котором значение левого потомка всегда меньше значение родителя ,а значение правого потомка больше родителя\n";
    string s; cin >> s; BinaryTree tree(s);tree.Print();
    cout << "Рекурсивный прямой обход дерева\n";
    tree.InOrder(tree.getroot());
    cout << "\nРекурсивный центрический обход дерева\n";
    tree.LevelOrder(tree.getroot());
    cout << "\nРекурсивный концевой обход дерева\n";
    tree.PostOrder(tree.getroot());
    cout << "\nНерекурсивный прямой обход дерева\n";
    tree.NoRecursive();
    string command;
    cout << "\nЕсли вы желаете добавит новое значениеи в БНП введите add\n";
    cout << "Если вы желаете удалить значение в БНП введите del\n";
    cout << "Если вы желаете найти н значениеи в БНП введите find\n";
    cout << "Введите exit, чтобы выйти\n";
    bool flag = true;
    while(flag) {
        int x;
        cin >> command;
        if(command!="exit") {
            cout << "Введите значение ";
            cin >> x;
        }
        if (command == "add") {
            tree.Add(x, tree.getroot());
            tree.Print();
        }
        if (command == "del") {
            cout << "\n";
            tree.DeleteNode(tree.getroot(), x);
            tree.Print();
        }
        if (command == "find"){
            if(tree.Find(x,tree.getroot()))
                cout << "Нашли элемент\n";
            else cout << "Такого элемента нет\n";
        }
        if (command == "exit") flag = false;
    }
}
void MenuLab18(){
    cout << "Введите количество элементов в массиве ";
    int size;
    cin >> size;
    int arr[size];
    FillArray(arr,size);
    BinaryTree tree;
    for(int i = 0; i < size;i++){
        tree.Add(arr[i],tree.getroot());
    }
    tree.LevelOrder(tree.getroot());
}
int main() {
  MenuLab18();
  return 0;
}

