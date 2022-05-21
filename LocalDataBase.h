#pragma once
#include <string>
#include "FileDataBase.h"
#include "Parser.h"

using namespace std;

const int UserLimit = 20;
const int UserFieldsCount = 8;

class LocalDataBase
{
private:
	static string*** Users;
    static string BD[UserLimit][UserFieldsCount][2];

public:
    static int UserLastId;
	static void Init() {
		string* lines = FileDataBase::Get();
        string* userDataFields = new string[8];
        string* userDataValue = new string[2];

        UserLastId = 0;

        for (int i = 0; i < UserLimit; i++)
        {
            userDataFields = Parser::Parse(lines[i], "|");

            for (int j = 0; j < UserFieldsCount; j++) {
                userDataValue = Parser::Parse(userDataFields[j], ":");
                BD[UserLastId][j][0] = userDataValue[0];
                BD[UserLastId][j][1] = userDataValue[1];
            }
            UserLastId++;
        }
	}

};