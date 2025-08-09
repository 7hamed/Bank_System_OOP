#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsUserListScreen : protected clsScreen
{
private:
	static void _printUserRecordLine(clsUser user)
	{
		cout << "| " << setw(18) << left << user.UserName;
		cout << "| " << setw(30) << left << user.fullName();
		cout << "| " << setw(15) << left << user.Phone;
		cout << "| " << setw(20) << left << user.Email;
		cout << "| " << setw(10) << left << user.Password;
		cout << "| " << setw(10) << left << user.Permission;
	}


public:
	static void showUserListScreen()
	{
		vector<clsUser> vUsers = clsUser::getUserList();
		
		string subtitle = "(" + to_string(vUsers.size()) + ") User(s)";
		_printScreenHeader("User List Screen", subtitle);

		cout << "\n______________________________________________________________________";
		cout << "____________________________________________\n";
		cout << "| " << setw(18) << left << "UserName";
		cout << "| " << setw(30) << left << "Full Name";
		cout << "| " << setw(15) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "Password";
		cout << "| " << setw(10) << left << "Permission";
		cout << "\n______________________________________________________________________";
		cout << "____________________________________________\n";

		if (vUsers.size() == 0)
		{
			cout << "\n   no client avaliable in system \n";
		}
		else
		{
			for (clsUser u : vUsers)
			{
				_printUserRecordLine(u);
				cout << endl;
			}
		}
		cout << "______________________________________________________________________";
		cout << "____________________________________________\n";

	}


};

