#pragma once
#include "BankUser.h"
const int usersLength = 20;

class BankDB
{
public:
	int bankUsersDBLength;
	BankUser bankUsersDB[usersLength];
	int usersCount = 0;
	int usersLastId = -1;
	void addUser(BankUser bankuser) {
		bankUsersDB[usersCount] = bankuser;
		usersCount++;
		usersLastId++;
	}
	BankUser lastUser() {
		return bankUsersDB[usersLastId];
	}
	BankUser* allUsers() {
		return bankUsersDB;
	}
};

