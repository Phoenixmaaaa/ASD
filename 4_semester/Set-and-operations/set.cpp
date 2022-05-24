
#include <vector>
#include <iostream>
#include "myAlgo.cpp"
using namespace std;
class mySet { //Множество - это отсортированный набор уникальных элементов единой природы
private:
    vector<int> set;
public:
    mySet(){
    }
    mySet(vector<int> b){
        QuickSort(b);
        for(int i = 0;i < b.size();i++){
            set.push_back(b.at(i));
        }
    }
    void printSet(){
        if(set.size() > 0) {
            for (int i = 0; i < set.size(); i++) {
                cout << set[i] << " ";
            }
        }
        else cout << "it's empty set\n";}
    mySet operator * (mySet B) {
        vector<int> v;
        int ourSize = set.size();
        int otherSize = B.getSize();
        int i = 0; int j = 0;
        while(i < ourSize && j < otherSize){
            if(set[i] == B[j]) {
                v.push_back(set[i]);
                i++; j++;
            }
            else {
                if(set[i] < B[j])
                    i++;
                else
                    j++;
            }
        }
        mySet C(v);return v;
    } //Пересечение мн-в А,B - это мн-в С, только с теми элементами из А,В, которые одновременно принадлежат обоим мн-вам.
    mySet operator / (mySet B){
        vector<int> v;
        int ourSize = set.size();
        int otherSize = B.getSize();
        int i = 0; int j = 0;
        while(i < ourSize && j < otherSize){
            if(set[i] == B[j]) {
                i++; j++;
            }
            else {
                if(set[i]<B[j]){
                    v.push_back(set[i]);
                    i++;
                }
                else j++;}
        }mySet C(v);return C;

    } //Разность мн-в А,В - это мн-в С,в которое входят только те элементы А, которые не совпадают с В.
    mySet operator + (mySet B){
        vector<int> sumVector;
        int sizeSet = set.size();
        int sizeB = B.getSize();
        for(int i = 0; i < sizeSet; i++){
            sumVector.push_back(set[i]);
        }
        for(int j = 0; j < sizeB; j++){
            sumVector.push_back(B[j]);
        }
        mySet C(sumVector);
        return C;

    } //Объединение мн-в А,В - это мн-в С с элементами из А,B без дублей.
    bool operator == (mySet B){
        int sizeSet = set.size();
        int sizeB = B.getSize();
        if(sizeSet!=sizeB) return false;
        for(int i = 0; i < sizeSet; i++){
            if(set[i]!=B[i]) return false;
        }
        return true;
    } //Равные мн-в это такие мн-в, которые состоят из одинаковых элементов
    bool in (mySet B){
        vector <int> C;
        int ourSize = set.size();
        int otherSize = B.getSize();
        int i = 0; int j = 0;
        while(i < ourSize && j < otherSize){
            if(set[i] == B[j]) {
                C.push_back(B[j]);
                i++; j++;
            }
            else {
                if(set[i] < B[j])
                    i++;
                else
                    j++;
            }
        }
        if(set==C) return  true;
        else return false;
    } // Мн-в А принадлежит мн-ву В, если все элементы из А содеражться в В.

    int operator [] (int i){
        return set.at(i);
    }
    int getSize() const {
        return set.size();
    }



};
#endif //UZHUN_SETOPERATION_MYSET_H
