#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
{
private:
	static void _readClientInfo(clsBankClient& client)
	{
		cout << "enter first Name : ";
		client.FirstName = clsInputValidate::readString();

		cout << "enter Last Name : ";
		client.LastName = clsInputValidate::readString();

		cout << "enter email : ";
		client.Email = clsInputValidate::readString();

		cout << "enter phone : ";
		client.Phone = clsInputValidate::readString();

		cout << "enter pin code : ";
		client.PinCode = clsInputValidate::readString();

		cout << "enter balance : ";
		client.Balance = clsInputValidate::readDblNumber();
	}

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
	static void showUpdateClientScreen()
	{
		
		if (!_checkAccessRights(clsUser::enPermission::pUpdateClient))
		{
			return;
		}
		
		_printScreenHeader("Update Client Screen");

		string accNumber = "";
		cout << "enter Account Number : ";
		accNumber = clsInputValidate::readString();
		
		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "account number not found, enter another one : ";
			accNumber = clsInputValidate::readString();
		}

		clsBankClient client = clsBankClient::find(accNumber);

		_printClient(client);

		char answer = 'n';
		cout << "\n do u want to update this client [y-YES | n-NO] : ";
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			cout << "\n --- updating client --- \n\n";
			_readClientInfo(client);

			clsBankClient::enSaveResults saveResult = client.save();

			switch (saveResult)
			{
			case clsBankClient::enSaveResults::svSucceeded:
				cout << "\n\t [Client Updated Successfully] \n";
				_printClient(client);
				break;

			case clsBankClient::enSaveResults::svFaildEmptyObject:
				cout << "\n\t [!] client not updated becuz client its empty. \n";
				break;
			}

		}
		else
		{
			cout << "\n\t [!] client not updated. \n";
		}

	}
};

