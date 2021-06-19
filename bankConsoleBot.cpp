#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <Windows.h>
//#include <vector>
#include "BankUser.h"
#include "BankDB.h"

using namespace std;

void registerUser();
int startScreen();
void creditScreen();
void manager();
void cartInfoScreen();
void cartScreen();
void printQuestionInConsole(string printedLine);
void initializeDB();
void addUserInArray(string userName, string userSurname, string userPatronymic, string userAddress, int userAge);

BankDB bankDB;
int usersCount = 0;

void initializeDB() {
    addUserInArray("Imya1", "Faum", "asd", "asd", 12);
    addUserInArray("Imya2", "surn", "test", "asdasd", 15);
    addUserInArray("q235n", "qw65M", "Q3B4", "13", 15);
}


void addUserInArray(string userName, string userSurname, string userPatronymic, string userAddress, int userAge) {
    BankUser newUser = BankUser(bankDB.usersCount, userName, userSurname, userPatronymic, userAddress, userAge);
    bankDB.addUser(newUser);
    cout << "Ваш номер карты: " << bankDB.lastUser().cart.getNumber() << "; Ваш пароль от карты: " << bankDB.lastUser().cart.getPass() << "\n";

    usersCount++;
}

void registerUser() {
    string userSurname, userName, userPatronymic, userAddress;
    int userAge;
    printQuestionInConsole("Введите вашу фамилию");
    cin >> userSurname;
    printQuestionInConsole("Введите вашe имя");
    cin >> userName;
    printQuestionInConsole("Введите ваше отчество (если есть)");
    cin >> userPatronymic;
    printQuestionInConsole("Введите ваш возраст");
    cin >> userAge;
    printQuestionInConsole("Введите адрес");
    cin >> userAddress;
    addUserInArray(userName, userSurname, userPatronymic, userAddress, userAge);
    manager();
}

int startScreen() {
    int userSelected;
    printQuestionInConsole("Выберите пункт меню \n 1) Операции с картой \n 2) Кредитные операции");
    cin >> userSelected;
    if (userSelected == 1 || userSelected == 2) {
        return userSelected;
    }
    else {
        return startScreen();
    }
}

void creditScreen() {
    int userSelected;
    printQuestionInConsole("Выберите пункт меню \n 1) Получить кредит \n 2) Вывод кредитной операции \n 3) Информация по текущему кредиту \n 4) Вернуться на главную");
    cin >> userSelected;
    if (userSelected == 1 || userSelected == 2 || userSelected == 3) {
        switch (userSelected)
        {
        case 1: // кредит - получение
            cout << "1";
            break;
        case 2: // кредит - история
            cout << "2";
            break;
        case 3: // кредит - информация
            cout << "3";
            break;
        case 5: // кредит - главная
            manager();
            break;
        default:
            break;
        }
    }
}

void manager() {
    switch (startScreen())
    {
    case 1: // карта
        cartScreen();
        break;
    case 2: // кредит
        creditScreen();
        break;
    default:
        break;
    }
}

void printQuestionInConsole(string printedLine) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
    cout << printedLine << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
}

void cartOperations(int userSelected, BankUser userCurrentUser) {
    switch (userSelected)
    {
    case 1: // карта - инфо - узнать баланс
        cout << userCurrentUser.cart.getMoney() << " руб" << endl;
        manager();
        break;
    case 2: // карта - инфо - снять
        int withdrawal;
        printQuestionInConsole("Введите сумму: ");
        cin >> withdrawal;
        if (withdrawal < userCurrentUser.cart.getMoney() && withdrawal > 0) {
            userCurrentUser.cart.setMoney(userCurrentUser.cart.getMoney() - withdrawal);
        }
        else {
            cout << "Недостаточно средств" << endl;
        }
        printQuestionInConsole("На карте: ");
        cout << userCurrentUser.cart.getMoney() << " руб" << endl;
        manager();
        break;
    case 3: // карта - инфо - внести
        int deposit;
        printQuestionInConsole("Введите сумму: ");
        cin >> deposit;
        if (deposit <= 0) {
            cout << "Некорректное число";
        }
        else {
            userCurrentUser.cart.setMoney(userCurrentUser.cart.getMoney() + deposit);
            printQuestionInConsole("На карте: ");
            cout << userCurrentUser.cart.getMoney() << " руб" << endl;
        }
        manager();
        break;
    case 4: // карта - инфо - назад
        cartScreen();
        break;
    case 5: // карта - инфо - главная
        manager();
        break;
    default:
        break;
    }
}

void cartInfoScreen() {
    bool hasUser = false, userLogIn = false;
    int uCartNumber, uCartPass, userSelected, userCurrentUserIndex;
    printQuestionInConsole("Введите номер карты");
    cin >> uCartNumber;
    printQuestionInConsole("Введите пароль");
    cin >> uCartPass;
    printQuestionInConsole("Выберите тип операции \n 1) Узнать баланс \n 2) Снять наличные \n 3) Внести наличные \n 4) Назад \n 5) Вернутся на главную");
    cin >> userSelected;

    for (int i = 0; i < bankDB.usersLastId + 1; i++) {
        if (bankDB.allUsers()[i].cart.getNumber() == uCartNumber) {
            hasUser = true;
            if (bankDB.allUsers()[i].cart.checkPass(uCartPass)) {
                userCurrentUserIndex = i;
            }
            else {
                cout << "Введён неверный пароль от карты";
            }
        }
    }
    if (!hasUser) {
        cout << "Не найден пользователь с данной картой\n";
        cartInfoScreen();
    }
    else {
        cartOperations(userSelected, bankDB.allUsers()[userCurrentUserIndex]);
    }
}

void cartScreen() {
    int userSelected;
    printQuestionInConsole("Выберите пункт меню \n 1) Открыть счет и карту \n 2) Операции с картой \n 3) Вернуться на главную");
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
            manager();
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
    initializeDB();
    manager();
}