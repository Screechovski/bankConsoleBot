#include <iostream>
#include <fstream>
#include <string>
#pragma once

using namespace std;

const string FilePath = "./bankUsersDB.txt";

class FileDataBase
{
public:
	static fstream fs;
	static int UsersCount;

	static void Save(string UsersData[20][8][2]) {
		for (int i = 0; i < 20; i++) {
			if (UsersData[i][1][1] != "") {
				FileDataBase::AddUser(i, UsersData[i][1][1], UsersData[i][2][1], UsersData[i][3][1], UsersData[i][4][1], UsersData[i][5][1], UsersData[i][6][1], UsersData[i][7][1]);
			}
		}
	}
	static void Clean() {
		FileDataBase::fs.open(FilePath, ios::out | ios::trunc);
		if (FileDataBase::fs.is_open()) {
			FileDataBase::fs << "";
		}
		FileDataBase::fs.close();
	}
	static string* Get() {
		string lineDB = "";
		string* lines = new string[20];

		UsersCount = 0;

		FileDataBase::fs.open(FilePath, fstream::app | fstream::in | fstream::out);
		if (FileDataBase::fs.is_open()) {
			while (!FileDataBase::fs.eof()) {
				FileDataBase::fs >> lineDB;
				if (lineDB.length() != 0) {
					lines[UsersCount] = lineDB;
					UsersCount++;
				}
			}
		}
		FileDataBase::fs.close();

		return lines;
	}

	static void AddUser(int userID, string userName, string userSurname, string userPatronymic, string userAge, string userCartMoney, string userCartNumber, string userCartPin) {
		string maketUser = "\nid:" + to_string(userID) + "|name:" + userName + "|surname:" + userSurname + "|patronymic:" + userPatronymic + "|age:" + userAge + "|cartMoney:" + userCartMoney + "|cartNumber:" + userCartNumber + "|cartPin:" + userCartPin;
		FileDataBase::fs.open(FilePath, fstream::app | fstream::in | fstream::out);
		if (FileDataBase::fs.is_open()) {
			FileDataBase::fs << maketUser;
		}
		FileDataBase::fs.close();
	}
};

