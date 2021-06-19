#pragma once
#include <string>
using namespace std;
class Date {
public:
    int day;
    int mounth;
    int year;
    Date() {
        day = 0;
        mounth = 0;
        year = 0;
    }
    Date(int d, int m, int y) {
        day = d;
        mounth = m;
        year = y;
    }
};
