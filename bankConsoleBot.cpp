#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include "DataBase.h"
#include "UI.h"

using namespace std;

int userLastId = 0;
fstream fs;
string BD[20][8][2];
void addUserInDB(int userID, string userName, string userSurname, string userPatronymic, string userAge, string userCartMoney, string userCartNumber, string userCartPin);
string* parseUserLineDB(string lineDB, string delimiter);

void readBD();
void registerUser();
void cartInfoScreen();
void cartScreen();

void addUserInDB(int userID, string userName, string userSurname, string userPatronymic, string userAge, string userCartMoney, string userCartNumber, string userCartPin) {
    string maketUser = "\nid:"+ to_string(userID) +"|name:" + userName + "|surname:"+ userSurname +"|patronymic:"+ userPatronymic +"|age:"+ userAge +"|cartMoney:"+ userCartMoney +"|cartNumber:"+ userCartNumber +"|cartPin:"+ userCartPin;
    fs.open("./bankUsersDB.txt", fstream::app | fstream::in | fstream::out);
    if (fs.is_open()) {
        fs << maketUser;
    }
    fs.close();
}


string* parseUserLineDB(string lineDB, string delimiter) {
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

void readBD() {
    /*string lineDB = "";
    string* userDataFields = new string[8];
    string* userDataValue = new string[2];
    int lineIndex = 0;
    fs.open("./bankUsersDB.txt", fstream::app | fstream::in | fstream::out);
    if (fs.is_open()) {
        while (!fs.eof()) {
            fs >> lineDB;
            if (lineDB.length() != 0) {
                userDataFields = parseUserLineDB(lineDB, "|");

                for (int i = 0; i < 8; i++) {
                    userDataValue = parseUserLineDB(userDataFields[i], ":");
                    BD[lineIndex][i][0] = userDataValue[0];
                    BD[lineIndex][i][1] = userDataValue[1];
                }
                lineIndex++;
            }
        }
    }
    userLastId = lineIndex;
    fs.close();*/

    string* Users = DataBase::Get();
    string* userDataFields = new string[8];
    string* userDataValue = new string[2];
    int lineIndex = 0;

    for (int i = 0; i < 20; i++) {
        userDataFields = parseUserLineDB(Users[i], "|");

        for (int i = 0; i < 8; i++) {
            userDataValue = parseUserLineDB(userDataFields[i], ":");
            BD[lineIndex][i][0] = userDataValue[0];
            BD[lineIndex][i][1] = userDataValue[1];
        }
        lineIndex++;
    }
}

void clearBD() {
    fs.open("./bankUsersDB.txt", ios::out | ios::trunc);
    if (fs.is_open()) {
        fs << "";
    }
    fs.close();
}

void saveBD() {
    string* lines = new string[20];

    for (int i = 0; i < 20; i++) {
        if (BD[i][1][1] != "") {
            lines[i] = "id:" + to_string(i) + "|name:" + BD[i][1][1] + "|surname:" + BD[i][2][1] + "|patronymic:" + BD[i][3][1] + "|age:" + BD[i][4][1] + "|cartMoney:" + BD[i][5][1] + "|cartNumber:" + BD[i][6][1] + "|cartPin:" + BD[i][7][1] + "\n";

        }
    }

    DataBase::AddUsers(lines);
}

void registerUser() {
    string userSurname, userName, userPatronymic, userAge, cartNumber, cartPin;
    UI::Print("Введите вашу фамилию(латиница)");
    cin >> userSurname;
    UI::Print("Введите вашe имя(латиница)");
    cin >> userName;
    UI::Print("Введите ваше отчество(латиница)");
    cin >> userPatronymic;
    UI::Print("Введите ваш возраст");
    cin >> userAge;
    if (stoi(userAge) < 18) {
        UI::Print("Ваш возраст меньше 18.");
        return cartScreen();
    }
    srand(time(NULL));
    cartNumber = to_string(1000 + rand() % 9000);
    cartPin = to_string(10 + rand() % 90);
    cout << "Ваш номер карты: " << cartNumber << "; Ваш пароль от карты: " << cartPin << "\n";
    BD[userLastId][0][0] = "id";
    BD[userLastId][0][1] = "";
    BD[userLastId][1][0] = "name";
    BD[userLastId][1][1] = userName;
    BD[userLastId][2][0] = "surname";
    BD[userLastId][2][1] = userSurname;
    BD[userLastId][3][0] = "patronymic";
    BD[userLastId][3][1] = userPatronymic;
    BD[userLastId][4][0] = "age";
    BD[userLastId][4][1] = userAge;
    BD[userLastId][5][0] = "cartMoney";
    BD[userLastId][5][1] = "0";
    BD[userLastId][6][0] = "cartNumber";
    BD[userLastId][6][1] = cartNumber;
    BD[userLastId][7][0] = "cartPin";
    BD[userLastId][7][1] = cartPin;
    userLastId++;
    clearBD();
    saveBD();
    cartScreen();
}

void cartOperations(int userSelected, int DBIndex) {
    int oldMoney;
    switch (userSelected)
    {
    case 1: // карта - инфо - узнать баланс
        cout << BD[DBIndex][5][1] << " руб" << endl;
        cartScreen();
        break;
    case 2: // карта - инфо - снять
        int withdrawal;
        oldMoney = stoi(BD[DBIndex][5][1]);
        UI::Print("Введите сумму: ");
        cin >> withdrawal;
        if (withdrawal < oldMoney && withdrawal > 0) {
            BD[DBIndex][5][1] = to_string(oldMoney - withdrawal);
        }
        else {
            cout << "Недостаточно средств или некорректная сумма поплнения" << endl;
        }
        UI::Print("На карте: ");
        cout << BD[DBIndex][5][1] << " руб" << endl;
        clearBD();
        saveBD();
        cartScreen();
        break;
    case 3: // карта - инфо - внести
        int deposit;
        oldMoney = stoi(BD[DBIndex][5][1]);
        UI::Print("Введите сумму: ");
        cin >> deposit;
        if (deposit <= 0) {
            cout << "Некорректное число";
        }
        else {
            BD[DBIndex][5][1] = to_string(oldMoney + deposit);
            UI::Print("На карте: ");
            cout << BD[DBIndex][5][1] << " руб" << endl;
        }
        clearBD();
        saveBD();
        cartScreen();
        break;
    case 4: // карта - инфо - главная
        cartScreen();
        break;
        break;
    default:
        break;
    }
}

void cartInfoScreen() {
    bool hasUser = false, userLogIn = false;
    string uCartNumber, uCartPass, userCurrentUserIndex;
    int userSelected;
    UI::Print("Введите номер карты");
    cin >> uCartNumber;
    UI::Print("Введите пароль");
    cin >> uCartPass;
    UI::Print("Выберите тип операции \n 1) Узнать баланс \n 2) Снять наличные \n 3) Внести наличные \n 4) Вернутся на главную");
    cin >> userSelected;

    if (userSelected == 4) {
        return cartScreen();
    }
    for (int i = 0; i < 20; i++) {
        if (BD[i][1][1] != "") {
            if (BD[i][6][1] == uCartNumber) {
                hasUser = true;
                if (BD[i][7][1] == uCartPass) {
                    userLogIn = true;
                    cartOperations(userSelected, i);
                }
                else {
                    break;
                }
            }
        }
    }
    if (!hasUser) {
        cout << "Не найден пользователь с данной картой\n";
        cartScreen();
    }
}

void cartScreen() {
    int userSelected;
    UI::Print("Выберите пункт меню \n 1) Открыть счет и карту \n 2) Операции с картой \n 3) Вернуться на главную");
    cin >> userSelected;
    if (userSelected == 1 || userSelected == 2 || userSelected == 3) {
        switch (userSelected)
        {
        case 1: // карта - заказать
            registerUser();
            break;
        case 2: // карта - инфо
            cartInfoScreen();
            break;
        case 3: // карта - главная
            cartScreen();
            break;
        default:
            break;
        }
    }
    else {
        return cartScreen();
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "Hello World!\n" << endl;

    readBD();
    cartScreen();
}