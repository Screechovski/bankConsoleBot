#include <iostream>
#include <fstream>
#include <string>
#pragma once

using namespace std;

const string FilePath = "./bankUsersDB.txt";
fstream FS;
int UsersCount;

class DataBase
{
public:

	/*static void Save(string UsersData[20][8][2]) {
		for (int i = 0; i < 20; i++) {
			if (UsersData[i][1][1] != "") {
				DataBase::AddUser(i, UsersData[i][1][1], UsersData[i][2][1], UsersData[i][3][1], UsersData[i][4][1], UsersData[i][5][1], UsersData[i][6][1], UsersData[i][7][1]);
			}
		}
	}*/

	static string* Parse(string lineDB, string delimiter){
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

	static void Clean() {
		FS.open(FilePath, ios::out | ios::trunc);
		if (FS.is_open()) {
			FS << "";
		}
		FS.close();
	}

	static string* Get() {
		string line = "";
		string* lines = new string[20];

		UsersCount = 0;

		FS.open(FilePath, fstream::app | fstream::in | fstream::out);
		if (FS.is_open()) {
			while (!FS.eof()) {
				FS >> line;
				if (line.length() != 0) {
					FS >> lines[UsersCount];
				}
			}
		}
		FS.close();

		return lines;
	}
	
	/*static void AddUser(string line) {
		FS.open(FilePath, fstream::app | fstream::in | fstream::out);
		if (FS.is_open()) {
			FS << line;
		}
		FS.close();
	}*/

	static void AddUsers(string * lines) {
		FS.open(FilePath, fstream::app | fstream::in | fstream::out);
		if (FS.is_open()) {
			for (int i = 0; i < 20; i++) {
				if (lines[i] != "") {
					FS << lines[i];
				}
			}
		}
		FS.close();
	}
};