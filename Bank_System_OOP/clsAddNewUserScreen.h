#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:
	static void _readUserInfo(clsUser& user)
	{
		cout << "enter first name : ";
		user.FirstName = clsInputValidate::readString();

		cout << "enter last name : ";
		user.LastName = clsInputValidate::readString();

		cout << "enter phone : ";
		user.Phone = clsInputValidate::readString();

		cout << "enter email : ";
		user.Email = clsInputValidate::readString();

		cout << "enter password : ";
		user.Password = clsInputValidate::readString();

		cout << "enter permission... \n";
		user.Permission = _readPermissionsToSet();
	}

	static int _readPermissionsToSet()
	{
		char answer = 'n';
		cout << "do u want to give full access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			return -1;
		}

		int permissions = 0;

		cout << "do u want to give Client List access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pClientList;
		}

		cout << "do u want to give Add New Client access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pAddNewClient;
		}

		cout << "do u want to give Delete Client access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pDeleteClient;
		}

		cout << "do u want to give Update Client access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pUpdateClient;
		}

		cout << "do u want to give Find Client access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pFindClient;
		}

		cout << "do u want to give Transaction access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pTransaction;
		}

		cout << "do u want to give Manage User access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pManageUser;
		}

		cout << "do u want to give Login Registers access [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			permissions += clsUser::enPermission::pLoginRegister;
		}

		return permissions;
	}

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
	static void showAddNewUserScreen()
	{
		_printScreenHeader("Add New User Screen");

		string userName = "";
		cout << "enter username : ";
		userName = clsInputValidate::readString();
		while (clsUser::isUserExist(userName))
		{
			cout << "username is used, enter another one : ";
			userName = clsInputValidate::readString();
		}

		clsUser newUser = clsUser::getAddNewUserObject(userName);

		_readUserInfo(newUser);

		clsUser::enSaveResult saveResult = newUser.save();

		switch (saveResult)
		{
		case clsUser::enSaveResult::svSucceeded:
			cout << "\n\t [User Added Successfully] \n";
			_printUserInfo(newUser);
			break;

		case clsUser::enSaveResult::svFaildUserExists:
			cout << "\n\t [!] user name is used, can not add user. \n";
			break;

		case clsUser::enSaveResult::svFaildEmptyObject:
			cout << "\n\t [!] user is empty, can not add user. \n";
			break;
		}
		
	}
};

