#pragma once
#include <string>

using namespace std;

class Parser
{
public:
    static string* Parse(string lineDB, string delimiter) {
        size_t pos = 0;
        string token;
        string* userData = new string[9];
        int userDataIndex = 0;

        while ((pos = lineDB.find(delimiter)) != string::npos) {
            token = lineDB.substr(0, pos);
            userData[userDataIndex] = token;
            userDataIndex++;
            lineDB.erase(0, pos + delimiter.length());
        }
        userData[userDataIndex] = lineDB;
        return userData;
    }
};

