#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "clsGlobal.h"

#include "clsDate.h"

class clsLoginScreen : protected clsScreen
{
private:
	static bool _login(short NumberOfTry)
	{
		string userName = "";
		string password = "";
		bool isLoginFaild = false;
		short faildLoginNumber = 0;

		do
		{
			if (isLoginFaild)
			{
				faildLoginNumber++;
				cout << "\n\t [!] login faild, password / username not correct.";
				cout << "\n\t [!] you have " << NumberOfTry - faildLoginNumber
					<< " trails to login. \n\n";
			}

			if (faildLoginNumber == NumberOfTry)
			{
				cout << "\n\t [!!!] you are locked after " << NumberOfTry << " faild trails \n";
				return false;
			}

			cout << "enter username : ";
			userName = clsInputValidate::readString();

			cout << "enter password : ";
			password = clsInputValidate::readString();

			CurrentUser = clsUser::find(userName, password);
			isLoginFaild = CurrentUser.isEmpty();

		} while (isLoginFaild);

		CurrentUser.registerLogin();
		clsMainScreen::showMainMenu();
		return true;
	}

public:
	static bool showLoginScreen()
	{
		system("cls");

		_printScreenHeader("Login Screen");

		return _login(3);
	}

};
