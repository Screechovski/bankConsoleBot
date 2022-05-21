#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class UI
{
public:
    static void Print(string printedLine) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
        cout << printedLine << endl;
        SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
    }
};