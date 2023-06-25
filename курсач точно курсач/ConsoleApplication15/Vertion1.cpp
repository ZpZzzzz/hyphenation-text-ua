#include <sstream>
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cstring>
using namespace std;
void per(string ch1, int m);
string ret(string ch, int count) {
    ifstream in("D:\\SomeText.txt"); // окрываем файл для чтения
    string ch1;
    if (in.is_open()) {
        // in.ignore(2356, "\n");
        for (int i = 0; i < count; i++) {
            in >> ch;
            cout << ch << endl;
            if (i == 0) {ch1 = ch;}     //перед первым словом не ставлю пробел
            else {ch1 = ch1 + " " + ch;}
            
        }
        cout << ch1 << endl;
        in.close();     // закрываем файл
    }
    return ch1;
}

int numberWords() {     //считает кол-во слов в строке
    char str[25000];
    int count = 1;
    FILE* stream;
    errno_t err;
    err = fopen_s(&stream, "D:\\SomeText.txt", "r");
    if (err == 0)
    {
        fgets(str, 25000, stream);
        for (int i = 0; i < strlen(str); i++)
        {
            if (str[i] == ' ')
            {
                count++;
            }
        }
    }
    return count;
}   

/*
void ent() {
    cout << "Enter your text: ";
    string text;
    getline(cin, text); // полностью извлекаем строку в переменную myName
}*/

int main() {
    SetConsoleCP(1251);				//ру ввод и вывод
    SetConsoleOutputCP(1251);
        string ch;
        int m;
        int count = numberWords();
        string ch1 = ret(ch, count);
        cout << "Введите длину строк: ";
        cin >> m;
        per(ch1, m);
}
    
int lenght(string ch1, int m) {         //cчитает примерное(!) кол-во полученных строк
    if (ch1.length() % m == 0) {
        return ch1.length() / m;
    }
    else { return ch1.length() / m + 1; }
}

void per(string ch1, int m) {
    string gol = "уеїєюоаиія'ь.,:!?";
    string pr = "бвгґджзйклмнпрстфхцчшщ";
    size_t found = 0;
    size_t found2 = 0;
    string ch2;
    for (int i = 0; i < lenght(ch1, m); i++){
        ch2 = ch1.substr(found2, m);
        if (i == 0) {
            //убираю первый -
            found = ch2.find_last_of(gol);
            cout << ch1.substr(found2, found + 1);
            found2 = found2 + found + 1;
        }
        else {
            found = ch2.find_last_of(gol); //Поиск по строке сh2 для последнего символа, который соответствует любому элементу строки vowel
            cout << '-' << endl << ch1.substr(found2, found + 1);
            found2 = found2 + found + 1;
        }
        
      //  ch2 = ch1.substr(found + 1, found + 1 + m);
    }
    

}

