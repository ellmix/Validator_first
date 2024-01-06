#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;


//Валидатор для файла html на проверку тегов < >

bool validateHTML(const string& filename) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return 0;
    }

    stack<char> tagStack;
    string line;
    int lineNumber = 0;

    while (getline(inFile, line)) {
        lineNumber++;

        for (char& c : line) {
            if (c == '<') {
                tagStack.push(c);
            }
            else if (c == '>') {
                if (tagStack.empty()) {
                    cerr << "Eror на строке " << lineNumber << ": Отсутствует открывающий тег <" << endl;
                    return 0;
                }
                else {
                    tagStack.pop();
                }
            }
        }
    }

    inFile.close();

    if (!tagStack.empty()) {
        cerr << "Error: Файл содержит непарные теги. Не хватает закрывающего тега >" << endl;
        return 0;
    }

    cout << "Файл " << filename << " успешно проверен на валидность." << endl;
    return 1;
}

int main() {

    setlocale(LC_ALL, "");

    string filename = "index.html";

    if (validateHTML(filename)) {
        cout << "HTML файл валиден." << endl;
    }
    else {
        cout << "HTML файл не валиден." << endl;
    }

    return 0;
}
