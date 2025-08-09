#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
private:
	static void _printUserInfo(clsUser user)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << user.FirstName;
		cout << "\nLastName    : " << user.LastName;
		cout << "\nFull Name   : " << user.fullName();
		cout << "\nEmail       : " << user.Email;
		cout << "\nPhone       : " << user.Phone;
		cout << "\nUser Name   : " << user.UserName;
		cout << "\nPassword    : " << user.Password;
		cout << "\nPermission  : " << user.Permission;
		cout << "\n___________________\n";
	}


public:
	static void showFindUserScreen()
	{
		_printScreenHeader("Finde User Screen");

		string userName = "";
		cout << "enter username : ";
		userName = clsInputValidate::readString();

		while (!clsUser::isUserExist(userName))
		{
			cout << "username not found, enter another one : ";
			userName = clsInputValidate::readString();
		}

		clsUser user1 = clsUser::find(userName);

		if (user1.isEmpty())
		{
			cout << "\n user is not found \n";
		}
		else
		{
			cout << "\n user is found :) \n";
		}

		_printUserInfo(user1);
	}



};

