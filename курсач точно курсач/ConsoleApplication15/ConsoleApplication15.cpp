
#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;
string huphWord(string ch1, int m, int i);
int huphenation(string word, int n);
int lenght(string ch1, int m);
string huphen(string word, int i);

//читає текст із файлу та перший рядок окремо
string reading(string input) {
    ifstream in(input);                          //відкриваємо файл для читання 
    string text;
    if (in.is_open()) {
        getline(in, text);
        in.close();                              //закрываємо файл
        text = text + " ";
        cout << "Ваш текст: \n" << text << endl << endl;
    }
    else {
        cout << "Файл пошкоджено або шлях до нього вказано неправильно! Спробуйте знову: ";
        string input;
        getline(cin, input);
        text = reading(input);
    }
    return text;
}

//перевіряє слова на довжину (більше 1 голосної)
bool chek1(string word) {
    string vowel = "уеїєюоаиія";
    int counter = 0;
    size_t found = word.find_first_of(vowel);   //підрахунок кількості гласних
    while (found != -1)
    {
        counter++;
        found = word.find_first_of(vowel, found + 1);
    }
    if (counter < 2) {
        return false;
    }
    else { return true; }
}

//перевіряє наявність абревіатур
bool check2(string word) {
    int counter(0);
    for (int i = 0; i < word.length(); i++) {
        if ((word[i] <= 'Я') && (word[i] >= 'А')) {
            counter++;
        }
    }
    if (counter > 1) return false;
    else return true;
}

//відсіває слово для перенесення в кінці рядка
string huphWord(string text, int m) {
    string word;
    word = text.substr(text.find_last_of(' ', m - 1) + 1, text.find_first_of(' ', m) - text.find_last_of(' ', m - 1) - 1);
    return word;
}

//відправляє в кор індекси змінних після яких можна ставити переноси
int huphenation(string word, int n) {
    string vowel = "уеїєюоаиія'ьАУЕЇЄОИІЯ";
    string consonant = "бвгґджзйклмнпрстфхцчшщБВГҐДЖЗЙКЛМНПРСТФХЦЧШЩ";
    string punct = ".,!?;:";
    int* index = new int[20];

  //  cout << "Матриця слова: ";
    //створює масив з 1 - голосна, 0 - приголосна, -1 - знак пунктуації, 2 - дефіз
    for (int i = 0; i < word.length(); i++) {
        for (int j = 0; j < vowel.length(); j++) {
            if (word[i] == vowel[j]) {
                index[i] = 1;
            }
        }
        for (int j = 0; j < consonant.length(); j++) {
            if (word[i] == consonant[j]) {
                index[i] = 0;
            }
        }
        for (int j = 0; j < punct.length(); j++) {
            if (word[i] == punct[j]) {
                index[i] = -1;
            }
        }
      //  cout << index[i] << "\t";
    }
   // cout << endl;

    //індекси символів після яких можна ставити перенесення
    int r = 0;
    if (n + 1 == word.length()) { r = n + 1; }
    else if (n + 1 == 0) { r = 0; }
    else {
        for (int i = 0; i < word.length(); i++) {      //щоб не відокремлювалися знаки пунктуації
            if (index[i] == -1 && n > word.length() - 3) {
                n = word.length() - 3;
            }
        }
        
        if (chek1(word) && check2(word)) {
            if (index[n] == 1 && index[n + 1] == 0 && index[n + 2] == 1) { r = n + 1; }
            else if (index[n] == 1 && index[n + 1] == 0) {
                if (index[n - 1] == 1) { r = n; }
                else if (index[n - 2] == 1) { r = n - 1; }
                else if (index[n - 2] == 0 && index[n - 3] == 1) { r = n - 1; }
                else if (index[n - 2] == 0 && index[n - 3] == 0) { r = n - 2; }
            }

            else if (index[n] == 0 && index[n + 1] == 0) {
                if (index[n - 1] == 1) { r = n + 1; }
                if (index[n - 1] == 0) { r = n; }
            }
            else if (index[n] == 0 && index[n + 1] == 1) {
                if (index[n - 1] == 1) { r = n; }
                if (index[n - 1] == 0 && index[n - 2] == 1) { r = n; }
                else if (index[n - 1] == 0 && index[n - 2] == 0) { r = n - 1; }
            }
        }
    }
    return r;
}

//перенесить слова
string huphen(string word, int r) {                  //де r номери символів, після яких можна ставити перенесення
    string wordT, wordB;
    if (word.length() > r && r > 0) {                //r символів до перенесення
        wordT = word.substr(0, r);
        wordB = word.substr(r, word.length());
    }
    if (r == 0) { return "\n"; }
    else if (r == word.length()) { return word + "\n"; }
    else { return wordT + "-\n"; }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int m, q, y;
    string input;
    cout << "Виберіть режим введення тексту: \n" << "1 - Ручне введення\n" << "2 - Введення з файлу\n";
    for (int i = 0; ; i++) {                        //перевірка правильності вибору
        getline(cin, input);
        y = atoi(input.c_str());
        if (y == 1 || y == 2) { break; }
        else { cout << "Не правильний формат відповіді, прошу введіть лише цифру: \n"; }
    }
    string text;
    if (y == 1) {
        cout << "Введіть текст: \n";
        /*cin.ignore(32767, '\n');*/
        getline(cin, text);
     //   cout << "Ваш текст: \n" << text << endl << endl;
    }
    else {
        cout << "Введіть шлях до файлу: \n";
        string in;
        cin.ignore(32767, '\n');
        getline(cin, in);
        text = reading(in);
    }
  //  cout << "Всього символів: " << text.length() << endl;

    cout << "Введіть довжину рядків: ";
    for (int i = 0; ; i++) {                         //перевірка правильності вибору
        getline(cin, input);
        m = atoi(input.c_str());
        if (m != 0) { m -= 1; break; }
        else { cout << "Не правильний формат вибору, прошу вводіть тільки позитивні числа: "; }
    }

    int number_str = text.length() / m + 1;
    cout << "Результуюча кількість рядків: " << number_str << endl;

    for (int i = 0; i < number_str; i++) {
        string word = huphWord(text, m);
      //  cout << "\nСлово для перенесення: " << word << endl;

        int n = m - text.find_last_of(' ', m);          //номер символу після якого слідує розділ рядків
     //   cout << "Номер символу після якого слідує розділ рядків: " << n << endl;

        int r = huphenation(word, n - 1);                       // номер символу після якого можливе перенесення
      //  cout << "Номер символу після якого можливий переноc: " << r << endl;

        q = n - r;
     //   cout << "Зсув: " << q << endl;

        cout <</* "Результат: \n" <<*/ text.substr(0, m - n) + " " << huphen(word, r);
        word.clear();
        text = text.substr(m - q + 1, text.length());                   //тепер текст на 1 рядок коротший    
        if (text[0] == ' ') { text = text.substr(1, text.length()); }   //прибираю прогалини на початку рядка
    }
}