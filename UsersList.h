#pragma once
#include "DataBase.h"

using namespace std;

string BD[20][8][2];
int UsersCountL = 0;

class UsersList
{
public:
	static void Init() {
        string* Users = DataBase::Get();
        string* userDataFields = new string[8];
        string* userDataValue = new string[2];
        UsersCountL = 0;

        for (int i = 0; i < 20; i++) {
            userDataFields = DataBase::Parse(Users[i], "|");

            for (int i = 0; i < 8; i++) {
                userDataValue = DataBase::Parse(userDataFields[i], ":");
                BD[UsersCountL][i][0] = userDataValue[0];
                BD[UsersCountL][i][1] = userDataValue[1];
            }
            UsersCountL++;
        }
	}

    static void SaveUsers() {
        string* lines = new string[20];

        for (int i = 0; i < 20; i++) {
            if (BD[i][1][1] != "") {
                lines[i] = "id:" + to_string(i) + "|name:" + BD[i][1][1] + "|surname:" + BD[i][2][1] + "|patronymic:" + BD[i][3][1] + "|age:" + BD[i][4][1] + "|cartMoney:" + BD[i][5][1] + "|cartNumber:" + BD[i][6][1] + "|cartPin:" + BD[i][7][1] + "\n";
            }
        }

        DataBase::Clean();
        DataBase::AddUsers(lines);
    }

    static void AddUser(string userSurname, string userName, string userPatronymic, string userAge, string cartNumber, string cartPin) {
        BD[UsersCountL][0][0] = "id";
        BD[UsersCountL][0][1] = to_string(UsersCountL);
        BD[UsersCountL][1][0] = "name";
        BD[UsersCountL][1][1] = userName;
        BD[UsersCountL][2][0] = "surname";
        BD[UsersCountL][2][1] = userSurname;
        BD[UsersCountL][3][0] = "patronymic";
        BD[UsersCountL][3][1] = userPatronymic;
        BD[UsersCountL][4][0] = "age";
        BD[UsersCountL][4][1] = userAge;
        BD[UsersCountL][5][0] = "cartMoney";
        BD[UsersCountL][5][1] = "0";
        BD[UsersCountL][6][0] = "cartNumber";
        BD[UsersCountL][6][1] = cartNumber;
        BD[UsersCountL][7][0] = "cartPin";
        BD[UsersCountL][7][1] = cartPin;
        UsersCountL++;
    }

    static string GetBalance(int id) {
        return BD[id][5][1];
    }

    static void SetMoney(int id, string value) {
        BD[id][5][1] = value;
    }

    static int GetUserId(string cartNumber, string cartPass) {
        int userId = -1;

        for (int i = 0; i < 20; i++) {
            if (BD[i][1][1] != "") {
                if (BD[i][6][1] == cartNumber) {
                    if (BD[i][7][1] == cartPass) {
                        userId = i;
                        break;
                    }
                }
            }
        }

        return userId;
    }
};

