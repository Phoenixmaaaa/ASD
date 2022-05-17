#ifndef HASHTABLE14_HASHTAB_H
#define HASHTABLE14_HASHTAB_H
#include <iostream>
#include <string>
using std::string;


class HashTab {

private:

    struct Pair {  //Структура Pair которая представляет собой пару слово и значение (т.е. wordKey и value)
        string wordKey = "";
        int value = 0;
        Pair(string Key, int v){
            wordKey = Key;
            value = v;
        }
        Pair(){
            wordKey = "";
            int value = 0;
        }
    };

    int bufSize = 100000; //Размер массива Pair
    float amountKey = 0; //Количество ключей
    Pair * MainHashTab;//Массив PairОВ

    int Hash(string word){ //Хэш-функция, которая ставит строке в соответствие число
        int wordHash = 0;
        for( char i : word) wordHash +=i; //Используем ASCII
        return wordHash % bufSize;
    }

    int Find( string word){ // Поиск парам MainHashTab.
      int hashWord = Hash(word);
      //Ищем с начала до позиции равной HashWord в массиве MainHashTab
      for(int i = 0; i < hashWord;i++){
          Pair p = MainHashTab[i];
          if(p.wordKey == word || !p.value) return i;
      }
      //Ищем с позиции hashWord до конца массива
      for(int i = hashWord; i<bufSize; i++){
          Pair p = MainHashTab[i];
          if(p.wordKey == word || !p.value) return i;
      }
      return -1;
    }
    void Resize(){
        bufSize *= 2;//Увеличиваем буффер в два раза
        Pair *newHashTable = new Pair[bufSize]; //Новый массив куда перенесем данные из старой таблицы
        for(int j = 0; j < bufSize / 2; j++) //цикл от 0 до размера нашего старого MainHashTable
        {
            Pair p = MainHashTab[j]; //Текущая пара j
            int position = -1;
            int hashWord = Hash(p.wordKey); //Вычисляем хэш wordKey в текущей паре j
            //обход от позиции равной hashWord до конца
            for(int i = hashWord; i < bufSize && position == -1; i++){
                if(newHashTable[i].wordKey == p.wordKey) position = i; //Заносим пару из старой таблицы в новую
            }
            //обход от позиции равной 0 до позиции HashWord, если position == -1(т.е. прошлый цикл ничего не нашел)
            for(int i = 0; i < hashWord && position ==-1; i++){
                if(newHashTable[i].wordKey == p.wordKey) position = i;
            }
            newHashTable[position] = p;
        }
        delete []MainHashTab;
        MainHashTab = newHashTable;
    }

public:
    HashTab(){ //Конструктор класса HashTab
        bufSize = 100000;
        amountKey = 0;
      MainHashTab = new Pair [bufSize];
    }
    void Add(string word)
    {//Добавление нового слова в MainHashTab
        int hashWord = Hash(word);//Хэш слова word
        int position = Find(word);
        if(position == -1){
            Resize();
            Add(word);
            return;
        }
        if(MainHashTab[position].wordKey == word)
            MainHashTab[position].value++;
        else
            MainHashTab[position] = Pair(word,1);

        amountKey++;

    }
    string Print() //Печать таблицы MainHashTab
    {
        string result;
        for(int i = 0; i < bufSize; i++){
            Pair p = MainHashTab[i];
            if(p.value)
            {
                result += p.wordKey + " " + std::to_string(p.value) + "\n";
            }
        }
        return result;
    }
};
#endif //HASHTABLE14_HASHTAB_H
