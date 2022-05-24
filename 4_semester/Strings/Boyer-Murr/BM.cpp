//Алгоритм Бойера Мурра
bool contains(map<char, int> m, char c)
{
    if(m.find(c) != m.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
map <char,int> getHashTable(string s)
{
    map <char,int> table; // Ассоциативный массив в формате символ --> удаленность от конца строки
    table['*'] = s.length()-1; // Для любых символов, которые не содержаться в строке s
    for(int i = s.length()-2; i > -1; i--)
    {
        if(!contains(table,s[i])) // Если в первые встречаем символ
        {
            int value = (s.length()-1)-i;
            table.insert(make_pair(s[i],value));
        }
    }
    if(!contains(table,s[s.length()-1])) // Если последний символ строки раннее не был встречен
    {
        int value = s.length()-1;
        table.insert(make_pair(s[s.length()-1],value));
    }
    return table;
}
int BM_search(string s, string subS)
{
    map<char, int> offsetTable = getHashTable(subS); // Таблица хэшей
    if (s.length() < subS.length())
    {
        cout << "Длина подстроки больше чем длина строки";
        return -1;
    }
    int i = subS.length() - 1; // указатель на текущий символ строки
    int j = i; // указатель на текущий символ образца
    int k = i; // вспомогательный указатель тоже на строчку s
    while (j >= 0 && i <= s.length() - 1)
    {
        j = subS.length() - 1; // j изначально смотрит в последний символ образца
        k = i;
        while (j >= 0 && s[k] == subS[j])
        {
            k--;
            j--;
        }
        if(contains(offsetTable,s[i]))
            i += offsetTable[s[i]]; // значение по ключу s[i]
        else
            i+=offsetTable['*']; // двигаем на длину подстроки
    }
    if (k >= s.length() - subS.length()) // вышли за строку и ничего не нашли
        return -1;
    else
        return k + 1; // указатель на элемент строки, с которого начинается искомая подстрока
}


