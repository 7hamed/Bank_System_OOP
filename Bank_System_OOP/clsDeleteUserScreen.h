#pragma once
#include <iostream>
#include <iomanip>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
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
	static void showDeleteUserScreen()
	{
		_printScreenHeader("Delete User Screen");

		string userName = "";
		cout << "enter username : ";
		userName = clsInputValidate::readString();

		while (!clsUser::isUserExist(userName))
		{
			cout << "user not found, enter another one : ";
			userName = clsInputValidate::readString();
		}

		clsUser user1 = clsUser::find(userName);
		_printUserInfo(user1);

		char answer = 'n';
		cout << "do u want to delete this user [y-YES | n-NO] : ";
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			if (user1.Delete())
			{
				cout << "\n\t [Deleted Successfully] \n";
				_printUserInfo(user1);
			}
			else
			{
				cout << "\n\t [!] Delete not perform ERROR \n";
			}
		}
		else
		{
			cout << "\n\t [!] Delete Canceled \n";
		}
	}


};

