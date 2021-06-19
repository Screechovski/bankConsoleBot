#pragma once
#include <string>
#include <time.h>
using namespace std;

class UserCart {
private:
    int _number;
    int _pin;
    string _userName;
    bool _passQuery;
    int _money;
public:
    UserCart() {
        _passQuery = false;
        _number = 0;
        _pin = 0;
        _money = 0;
    }
    UserCart(string name) {
        srand(time(NULL));
        _number = 1000 + rand() % 9000;
        _pin = 10 + rand() % 90;
        _userName = name;
        _passQuery = false;
        _money = 0;
    }
    int getMoney() {
        return _money;
    }
    void setMoney(int count) {
        _money = count;
    }
    int getNumber() {
        return _number;
    }
    bool checkPass(int upass) {
        return _pin == upass;
    }
    int getPass() {
        if (!_passQuery) {
            _passQuery = true;
            return _pin;
        }
    }
};