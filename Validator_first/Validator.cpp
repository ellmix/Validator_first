#include <iostream>
#include <fstream>
#include <string>
#include <stack>

using namespace std;


//��������� ��� ����� html �� �������� ����� < >

bool validateHTML(const string& filename) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cerr << "�� ������� ������� ����: " << filename << endl;
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
                    cerr << "Eror �� ������ " << lineNumber << ": ����������� ����������� ��� <" << endl;
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
        cerr << "Error: ���� �������� �������� ����. �� ������� ������������ ���� >" << endl;
        return 0;
    }

    cout << "���� " << filename << " ������� �������� �� ����������." << endl;
    return 1;
}

int main() {

    setlocale(LC_ALL, "");

    string filename = "index.html";

    if (validateHTML(filename)) {
        cout << "HTML ���� �������." << endl;
    }
    else {
        cout << "HTML ���� �� �������." << endl;
    }

    return 0;
}
