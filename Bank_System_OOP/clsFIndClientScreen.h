#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;


class clsFIndClientScreen : protected clsScreen
{
private:
	static void _printClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << client.FirstName;
		cout << "\nLastName    : " << client.LastName;
		cout << "\nFull Name   : " << client.fullName();
		cout << "\nEmail       : " << client.Email;
		cout << "\nPhone       : " << client.Phone;
		cout << "\nAcc. Number : " << client.AccountNumber();
		cout << "\nPassword    : " << client.PinCode;
		cout << "\nBalance     : " << client.Balance;
		cout << "\n___________________\n";
	}


public:
	static void showFindClientScreen()
	{
		
		if (!_checkAccessRights(clsUser::enPermission::pFindClient))
		{
			return;
		}
		
		_printScreenHeader("Find Client Screen");

		string accNumber = "";
		cout << "enter account number : ";
		accNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "account number is not found, enter another one : ";
			accNumber = clsInputValidate::readString();
		}

		clsBankClient client = clsBankClient::find(accNumber);

		if (!client.isEmpty())
		{
			cout << "\n\t [!] client is found :) \n\n";
		}
		else
		{
			cout << "\n\t [!] client is not found :( \n\n";
		}

		_printClient(client);
	}


};

