include "iostream"
#include "string"
#include "math.h"
using namespace std;

#define B 13 // константа B
#define Q 997 // любое простое число

string get_sub_string(string s, int startPos, int lastPos)
{
    string subS;
    for (int k = startPos; k <= startPos+lastPos; k++)
    {
        if (k > s.length()-1) break;
        subS += s[k];
    }
    return subS;
} // Возвращает подстроку в интервале от startPos до lastPos
int get_hash(string s)
{
    int horner_hash = 0;
    for(int i = 0; i < s.length(); i++)
    {
        horner_hash = (B*horner_hash+int(s[i])) % Q; // метод Хорнера вычисления полиномиального многочлена
    }
    return horner_hash;
}

int search_pattern_in_string(string text, string pattern)
{
     int count_pattern = 0; // Возвращаемое значение функции - это количество совпадений в строке;
     int pattern_len = pattern.length();
     int text_len = text.length();
     if(text_len < pattern_len)
         return -1;
     int m = pow(B,pattern_len-1); // Значение B в максимально возможной степени

    //Находим хэш паттерна и хэш первой подстроки text
     int pattern_hash = get_hash(pattern);
     int text_hash = get_hash(get_sub_string(text,0,pattern_len-1)); // Хэш первой посдтроки длины паттерна
     // Проходим по каждому символу строки
    for (int i = 0; i < text_len - pattern_len + 1; i++)
     {
          if(pattern_hash == text_hash)
          {
              string s = get_sub_string(text,i,pattern_len-1);
              if(s==pattern)
                count_pattern++;
              else
                  cout << "Случилась коллизия" <<" ";
          }
          if(i < text_len - pattern_len)
            text_hash = ((text_hash - int(text[i]) * m) * B + int(text[i + pattern_len])) % Q; //Скользящий хэш
        if (text_hash < 0)
            text_hash += Q;
    }
    return count_pattern;
}

int main()
{
  string h = "bAAAoAAAbAAA";
  string subH = "AAA";
  return 0;
}
