#include <iostream>
#include <string>
#include <locale>
#include <conio.h>
#include <Windows.h>
#include <fstream>

using namespace std;

void addUsers();
void addUserInDB(int userID, string userName, string userSurname, string userPatronymic, string userAge, string userCartMoney, string userCartNumber, string userCartPin);
string* parseUserLineDB(string lineDB, string delimiter);
void printQuestionInConsole(string printedLine);
void readBD();
int userLastId = 0;
fstream fs;
string BD[20][8][2];
void registerUser();
int startScreen();
void creditScreen();
void manager();
void cartInfoScreen();
void cartScreen();

void addUsers() {
    addUserInDB(0,"Filatov", "Albert", "Vyacheslavovich", "32", "0", "1463", "14");
    addUserInDB(1,"Kalashnikov", "Ostap", "Maksimovich", "26", "0", "4286", "27");
    addUserInDB(2, "Blinova", "Birgit", "Mikhailovna", "26", "0", "4789", "94");
}

void addUserInDB(int userID, string userName, string userSurname, string userPatronymic, string userAge, string userCartMoney, string userCartNumber, string userCartPin) {
    string maketUser = "\nid:"+ to_string(userID) +"|name:" + userName + "|surname:"+ userSurname +"|patronymic:"+ userPatronymic +"|age:"+ userAge +"|cartMoney:"+ userCartMoney +"|cartNumber:"+ userCartNumber +"|cartPin:"+ userCartPin;
    fs.open("./bankUsersDB.txt", fstream::app | fstream::in | fstream::out);
    if (fs.is_open()) {
        fs << maketUser;
    }
    fs.close();
}

/* спизжено */
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
    string lineDB = "";
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
                    //cout << "строка " << lineIndex << " скобка" << i << endl;
                    userDataValue = parseUserLineDB(userDataFields[i], ":");
                    //cout << userDataValue[0] << endl;
                    //cout << userDataValue[1] << endl;

                    BD[lineIndex][i][0] = userDataValue[0];
                    BD[lineIndex][i][1] = userDataValue[1];
                }
                lineIndex++;
            }
        }
    }
    userLastId = lineIndex;
    fs.close();
}

void clearBD() {
    fs.open("./bankUsersDB.txt", ios::out | ios::trunc);
    if (fs.is_open()) {
        fs << "";
    }
    fs.close();
}

void saveBD() {
    for (int i = 0; i < 20; i++) {
        if (BD[i][1][1] != "") {
            addUserInDB(i, BD[i][1][1], BD[i][2][1], BD[i][3][1], BD[i][4][1], BD[i][5][1], BD[i][6][1], BD[i][7][1]);
        }
    }
}

void registerUser() {
    string userSurname, userName, userPatronymic, userAge, cartNumber, cartPin;
    printQuestionInConsole("Введите вашу фамилию(латиница)");
    cin >> userSurname;
    printQuestionInConsole("Введите вашe имя(латиница)");
    cin >> userName;
    printQuestionInConsole("Введите ваше отчество(латиница)");
    cin >> userPatronymic;
    printQuestionInConsole("Введите ваш возраст");
    cin >> userAge;
    if (stoi(userAge) < 18) {
        printQuestionInConsole("Ваш возраст меньше 18.");
        return manager();
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
    manager();
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

void printQuestionInConsole(string printedLine) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, FOREGROUND_GREEN);
    cout << printedLine << endl;
    SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY);
}

void cartOperations(int userSelected, int DBIndex) {
    int oldMoney;
    switch (userSelected)
    {
    case 1: // карта - инфо - узнать баланс
        cout << BD[DBIndex][5][1] << " руб" << endl;
        manager();
        break;
    case 2: // карта - инфо - снять
        int withdrawal;
        oldMoney = stoi(BD[DBIndex][5][1]);
        printQuestionInConsole("Введите сумму: ");
        cin >> withdrawal;
        if (withdrawal < oldMoney && withdrawal > 0) {
            BD[DBIndex][5][1] = to_string(oldMoney - withdrawal);
        }
        else {
            cout << "Недостаточно средств или некорректная сумма поплнения" << endl;
        }
        printQuestionInConsole("На карте: ");
        cout << BD[DBIndex][5][1] << " руб" << endl;
        clearBD();
        saveBD();
        manager();
        break;
    case 3: // карта - инфо - внести
        int deposit;
        oldMoney = stoi(BD[DBIndex][5][1]);
        printQuestionInConsole("Введите сумму: ");
        cin >> deposit;
        if (deposit <= 0) {
            cout << "Некорректное число";
        }
        else {
            BD[DBIndex][5][1] = to_string(oldMoney + deposit);
            printQuestionInConsole("На карте: ");
            cout << BD[DBIndex][5][1] << " руб" << endl;
        }
        clearBD();
        saveBD();
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
    string uCartNumber, uCartPass, userCurrentUserIndex;
    int userSelected;
    printQuestionInConsole("Введите номер карты");
    cin >> uCartNumber;
    printQuestionInConsole("Введите пароль");
    cin >> uCartPass;
    printQuestionInConsole("Выберите тип операции \n 1) Узнать баланс \n 2) Снять наличные \n 3) Внести наличные \n 4) Назад \n 5) Вернутся на главную");
    cin >> userSelected;

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
        //cartInfoScreen();
    }
    else {
        //cartOperations(userSelected, bankDB.allUsers()[userCurrentUserIndex]);
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
    readBD();
    manager();
}