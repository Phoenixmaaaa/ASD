
#ifndef INC_15LABBINARYTREE_BINARYTREE_H
#define INC_15LABBINARYTREE_BINARYTREE_H
#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;
struct NodeTree { //Приватная структура класса BinaryTree, которая представляет собой узел дерева
    int value; //Какие-то данные
    NodeTree *leftChild = nullptr;//Указатель на левого потомка
    NodeTree *rightChild = nullptr;//Указатель на правого потомка
    NodeTree() { //Базовый конструктор cтруктуры NodeTree
        value = 0;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    NodeTree(int value) { //Конструктор структуры NodeTree по значению
        this->value = value;
        leftChild = nullptr;
        rightChild = nullptr;
    }

    NodeTree(string &s) { //Конструктор структуры NodeTree по строке
        value = GetValue(s); // Получили значение
        s = s.erase(0, GetRank(value));//Перезаписали строку без value
        if (s[0] != '(') return; //База рекурсии
        s = DeletePairedBrackets(s);//Удаляем парные скобки, перезаписываем строку
        if (IsDigit(s[0]))
            leftChild = new NodeTree(s); //Конструткор для левого потомка от измененной s
        if (s[0] == ',' && IsDigit(s[1]))
            rightChild = new NodeTree(s.erase(0, 1));//Конструктор для правого потомка от s без запятой
    }
private:
    //Вспомогательные функции для конструктора класса NodeTree от строки
    bool IsDigit(char c) {
        return c>='0' && c<='9';
    } //Определяет является ли символ цифрой
    int GetRank(int n) {
        int rank = 1;
        while (n / 10 > 0) {
            n = n / 10;
            rank++;
        }
        return rank;
    } //Возвращает количество разрядов числа
    int GetValue(string s) {
        int n = s.size();
        int i = 1;
        while(i < n) {
            if(!IsDigit(s[i++])) break;
        }
        return stoi(s.substr(0,i));
    } //Возвращает первое встречающее в строке число
    string DeletePairedBrackets(string s) {
        for (int i = 1, length = 1; i < s.size(); i++, length += (s[i] == '(') - (s[i] == ')')) {
            if (!length) {
                return s.erase(0, 1).erase(i - 1, 1);
            }
        }
        return s;
    }//Удаление парных скобок
};

class BinaryTree { //Класс в котором содержатся функции для работы с бинарным деревом: печать дерева и рекурсивные способы обхода
private:
    NodeTree *root;
public:
    BinaryTree(int x) {//Базовый конструктор класса BinaryTree
        root = new NodeTree(x);
    }

    BinaryTree(string s) { //Конструктор класса BinaryTree по строке
        root = new NodeTree(s);
    }

    BinaryTree() {
        root = nullptr;
    }

    NodeTree *getroot() const { //Геттер
        return root;
    }

    void Print(string &s, NodeTree *node, bool flag) {
        //flag = 0,значит соединяем с родителем
        //flad = 1,значит соединяем с потомком
        if (!node) return; //Базовый случай рекурсии
        string parent = "└──";
        string child = "├──";
        string childToChild = "│   "; //Cвязь между потомками одного родителя
        string parentToChild = "    ";//Cвязь между родителем и потомком;
        string newStringS;
        if (node->value) {
            if (!flag) {
                std::cout << s << parent << node->value << "\n";
                newStringS = s + parentToChild;
            } else {
                std::cout << s << child << node->value << "\n";
                newStringS = s + childToChild;
            }
        }
        Print(newStringS, node->leftChild, true);
        Print(newStringS, node->rightChild, false);
    }

    void Print() {
        string s = "";
        NodeTree *node = root;
        bool flag = 0;
        string parent = "└──";
        string child = "├──";
        string childToChild = "│   "; //Cвязь между потомками одного родителя
        string parentToChild = "    ";//Cвязь между родителем и потомком;
        string newStringS;
        if (!flag) {
            cout << s << parent << node->value << "\n";
            newStringS = s + parentToChild;
        }
        Print(newStringS, node->leftChild, true);
        Print(newStringS, node->rightChild, false);
    }

    //Метод прямого обхода дерева:
    void InOrder(NodeTree *node) {
        if (!node) return; //1 База рекурсии: не является ли текущий узел пустым
        cout << node->value << " "; //2 Вывод value текущего NodeTree, то есть node->getValue();
        InOrder(node->leftChild); //3 Вызываем функцию прямого обхода для левого потомка
        InOrder(node->rightChild);//4 Вызываем функцию обхода для правого потомка
    }

    //Метод концевого обхода дерева:
    void PostOrder(NodeTree *node) {
        if (!node) return; //1 База рекурсии: не является ли текущий узел пустым
        PostOrder(node->leftChild);  //2 Обходим левое поддерево рекурсивно, вызвав функцию обратного обхода.
        PostOrder(node->rightChild);//3 Обходим правое поддерево рекурсивно, вызвав функцию обратного обхода.
        cout << node->value << " "; //4 Показываем поле данных корня (или текущего узла).
    }

    //Метод центрического обхода дерева:
    void LevelOrder(NodeTree *node) {
        if (!node) return;//1 База рекурсии: не является ли текущий узел пустым
        LevelOrder(node->leftChild); //2.Обходим левое поддерево рекурсивно, вызвав функцию центрического обхода
        cout << node->value << " "; //3.Показываем поле данных корня (или текущего узла)
        LevelOrder(node->rightChild);//4.Обходим правое поддерево рекурсивно, вызвав функцию центрического обхода.
    }

    // Метод нерекурсивного прямого обхода дерева, реализованного с помощью стека:
    //Идея: так как стек это СД LIFO, то в начале распечается левое поддерево, а затем правое,что и нужно для прямого обхода
    void NoRecursive() {
        stack<NodeTree *> s;//1) Заводим стек s, в котором хранятся указатели на NodeTree
        s.push(root); //2) Кладем this->root в стек
        NodeTree *tree;// Заводим переменную указатель на NodeTree tree
        while (!s.empty() &&
               !tree) { //3) Пока стек не пуст, value вершины стека = tree, удаляем вершину стека, выводим в консоль tree
            tree = s.top();
            s.pop();
            cout << (tree->value) << " ";
            if (tree->rightChild)
                s.push(tree->rightChild); //4) Если правый потомок tree не nullptr, то добавляем в стек
            if (tree->leftChild) s.push(tree->leftChild);  //5) Если левый потомок tree не nullptr, то добавляем в стек
        }
    }

    //Метод добавления нового узла в дерево для работы с бинарными деревьями поиска(БНП):
    //Идея: БНП - бинарное дерево со свойсвтом: значение левого потомка меньше чем значение родителя, а значение правого потомка его больше
    void Add(int newValue, NodeTree *node) {
        if (!node) {
            root = new NodeTree(newValue);
            return;
        }
        if (newValue >= node->value &&
            node->rightChild) //Если добавляемое значение больше чем родитель узла node и правый поток node не пустой
            Add(newValue, node->rightChild); //Рекурсивно вызываем эту же функцию для правого
        if (newValue >= node->value && !node->rightChild) { //База рекурсии для правого потомка
            node->rightChild = new NodeTree(newValue);
        }
        if (newValue < node->value &&
            node->leftChild) //Если добавляемое значение меньше чем родитель узла node и левый поток node не пустой
            Add(newValue, node->leftChild); //Рекурсивно вызываем эту же функцию для левого
        if (newValue < node->value && !node->leftChild) {//База рекурсии для левого потомка
            node->leftChild = new NodeTree(newValue);
        }
    }

    //Метод поиска узла в дереве.
    //Идея: аналогично методу Add, опираемся на понятие БНП
    NodeTree *Find(int findValue, NodeTree *node) {
        if (findValue == node->value) return node;
        if (findValue > node->value && node->rightChild) return Find(findValue, node->rightChild);
        if (findValue < node->value && node->leftChild) return Find(findValue, node->leftChild);
        return nullptr;
    }

    NodeTree *DeleteNode(NodeTree *aBranch, int aData) {
        if (aBranch == NULL)
            return aBranch;
        if (aData == aBranch->value) {
            NodeTree *tmp;
            if (aBranch->rightChild == NULL)
                tmp = aBranch->leftChild;
            else {
                NodeTree *ptr = aBranch->rightChild;
                if (ptr->leftChild == NULL) {
                    ptr->leftChild = aBranch->leftChild;
                    tmp = ptr;
                } else {
                    NodeTree *pmin = ptr->leftChild;
                    while (pmin->leftChild != NULL) {
                        ptr = pmin;
                        pmin = ptr->leftChild;
                    }
                    ptr->leftChild = pmin->rightChild;
                    pmin->leftChild = aBranch->leftChild;
                    pmin->rightChild = aBranch->rightChild;
                    tmp = pmin;
                }
            }
            if (aBranch == this->root) {
                root = tmp;
                delete aBranch;
                return tmp;
            }
            delete aBranch;
            return tmp;
        } else if (aData < aBranch->value)
            aBranch->leftChild = DeleteNode(aBranch->leftChild, aData);
        else
            aBranch->rightChild = DeleteNode(aBranch->rightChild, aData);
        return aBranch;
    }
};
#endif //INC_15LABBINARYTREE_BINARYTREE_H
