#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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
	static void showDeleteClientScreen()
	{
		
		if (!_checkAccessRights(clsUser::enPermission::pDeleteClient))
		{
			return;
		}
		
		_printScreenHeader("Delete Client Screen");

		string accNumber = "";
		cout << "enter Account Number : ";
		accNumber = clsInputValidate::readString();
		
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "Account Number not found, choose another one : ";
			accNumber = clsInputValidate::readString();
		}

		clsBankClient client1 = clsBankClient::find(accNumber);

		_printClient(client1);

		char answer = 'n';
		cout << "\n do u want to delete this client [y-YES | n-NO] : ";
		cin >> answer;
		if (toupper(answer) == 'Y')
		{
			if (client1.Delete())
			{
				cout << "\n\t [Client Deleted Successfully] \n";
				_printClient(client1);
			}
			else
			{
				cout << "\n\t [!] error happen, client not deleted. \n";
			}
		}
		else
		{
			cout << "\n\t [!] client not deleted. \n";
		}

	}

};

