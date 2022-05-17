#ifndef HASHTABLE14_HASHTAB_H
#define HASHTABLE14_HASHTAB_H
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class HashTab {

private:
    struct Pair {  //Структура Pair которая представляет собой пару слово и значение (т.е. wordKey и value)
        string wordKey = "";
        int value = 0;
        Pair(string wordKey, int value){
            this ->wordKey = wordKey;
            this -> value = value;
        }
    };
    int bufSize = 10; //Количество векторов в массиве векторов MainHashTab;
    float amountKey = 0; //Количество ключей
    vector <Pair> *MainHashTab;//Массив векторов размерности bufSize

    int Hash(string word){ //Хэш-функция, которая ставит строке в соответствие число
        int wordHash = 0;
        for( char i : word) wordHash +=i; //Используем ASCII
        return wordHash % bufSize;
    }

    int Find(vector<Pair> V, string word){// Поиск по векторам MainHashTab, добавлено ли такое слово или нет.
        for(int i = 0; i < V.size(); i++) {
            Pair currentPair = V[i];
            if(currentPair.wordKey == word) return i; //Если слово встретилось возращает позицию пары, в которой это слово встретилось
        }
        return -1;
    }

public:
    HashTab(){//Конструктор класса HashTab
        bufSize = 10;
        amountKey = 0;
        MainHashTab = new vector<Pair>[bufSize];
    }
    void Add(string word)
    {//Добавление нового слова в MainHashTab
        int hashWord = Hash(word);//Хэш слова word и позиция вектора V в MainHashTab
        int position = Find(MainHashTab[hashWord],word);
        if(position == -1){
            Pair p(word,1);
            MainHashTab[hashWord].push_back(p);
            amountKey++;
        }
        else
            MainHashTab[hashWord][position].value++; // Если такая пара была найдена, то увеличь значение value данной пары на 1;

    }
    string Print() //Печать таблицы MainHashTab
    {
        string result;
        for(int i = 0; i < bufSize; i++){
            for(  Pair pair:MainHashTab[i]) {
                result += pair.wordKey + " " + std::to_string(pair.value) + "\n";
            }
        }
        return result;
    }
};
#endif //HASHTABLE14_HASHTAB_H
