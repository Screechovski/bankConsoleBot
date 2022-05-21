#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include "DataBase.h"
#include "UI.h"
#include "UsersList.h"

using namespace std;

void registerUser();
void cartOperations(int userSelected, int DBIndex);
void cartInfoScreen();
void cartScreen();

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
    UsersList::AddUser(userSurname, userName, userPatronymic, userAge, cartNumber, cartPin);
    UsersList::SaveUsers();
    cartScreen();
}

void PrintBalance(int id) {
    cout << UsersList::GetBalance(id) << " руб" << endl;
}

void WithdrawMoney(int id) {
    int withdrawal;
    int oldMoney = stoi(UsersList::GetBalance(id));
    UI::Print("Введите сумму: ");
    cin >> withdrawal;
    if (withdrawal < oldMoney && withdrawal > 0) {
        UsersList::SetMoney(id, to_string(oldMoney - withdrawal));
    }
    else {
        cout << "Недостаточно средств или некорректная сумма снятия" << endl;
    }
    UI::Print("На карте: ");
    cout << UsersList::GetBalance(id) << " руб" << endl;
    UsersList::SaveUsers();
}

void DepositMoney(int id) {
    int deposit;
    int oldMoney = stoi(UsersList::GetBalance(id));
    UI::Print("Введите сумму: ");
    cin >> deposit;
    if (deposit <= 0) {
        cout << "Некорректное число";
    }
    else {
        UsersList::SetMoney(id, to_string(oldMoney + deposit));
        UI::Print("На карте: ");
        cout << UsersList::GetBalance(id) << " руб" << endl;
    }
    UsersList::SaveUsers();
}

void cartOperations(int userSelected, int DBIndex) {
    switch (userSelected)
    {
    case 1: // карта - инфо - узнать баланс
        PrintBalance(DBIndex);
        cartScreen();
        break;
    case 2: // карта - инфо - снять
        WithdrawMoney(DBIndex);
        cartScreen();
        break;
    case 3: // карта - инфо - внести
        DepositMoney(DBIndex);
        cartScreen();
        break;
    case 4: // карта - инфо - главная
        cartScreen();
        break;
    default:
        break;
    }
}

void cartInfoScreen() {
    bool hasUser = false;
    bool userLogIn = false;
    string uCartNumber; 
    string uCartPass; 
    string userCurrentUserIndex;
    int userSelected;
    int userId;

    UI::Print("Введите номер карты");
    cin >> uCartNumber;
    UI::Print("Введите пароль");
    cin >> uCartPass;
    UI::Print("Выберите тип операции \n 1) Узнать баланс \n 2) Снять наличные \n 3) Внести наличные \n 4) Вернутся на главную");
    cin >> userSelected;

    if (userSelected == 4) {
        return cartScreen();
    }
    userId = UsersList::GetUserId(uCartNumber, uCartPass);
    if (userId == -1) {
        cout << "Пользователь не найден, или введен неверный pin\n";
        cartScreen();
    }
    else {
        cartOperations(userSelected, userId);
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

    UsersList::Init();
    cartScreen();
}