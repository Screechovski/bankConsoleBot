#pragma once
#include <string>
#include "UserCart.h"
#include "UserCredit.h"
using namespace std;

class BankUser {
public:
    int id;
    string name;
    string surname;
    string patronymic;
    string address;
    int age;
    UserCart cart;
    BankUser() {
        cart = UserCart();
        id = 21;
        name = "";
        surname = "";
        patronymic = "";
        address = "";
        age = 0;
    }
    BankUser(int pid, string pname, string psurname, string ppatronymic, string paddress, int apge) {
        id = pid;
        name = pname;
        surname = psurname;
        patronymic = ppatronymic;
        address = paddress;
        age = apge;
        cart = UserCart(pname);
    }
};