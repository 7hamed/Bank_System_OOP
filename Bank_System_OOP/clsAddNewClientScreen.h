#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
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
	static void showAddNewClientScreen()
	{
		
		if (!_checkAccessRights(clsUser::enPermission::pAddNewClient))
		{
			return;
		}
		
		_printScreenHeader("Add New Client Screen");

		string accNumber = "";
		cout << "enter Account Number : ";
		accNumber = clsInputValidate::readString();

		while (clsBankClient::isClientExist(accNumber)) // enter new account number
		{
			cout << "this account number is exist, enter another one : ";
			accNumber = clsInputValidate::readString();
		}

		clsBankClient newClient = clsBankClient::getAddNewClientObject(accNumber);

		_readClientInfo(newClient);

		clsBankClient::enSaveResults saveResult = newClient.save();

		switch (saveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\n\t [Client Added Successfully] \n\n";
			_printClient(newClient);
			break;

		case clsBankClient::enSaveResults::svFaildAccountNumberExist:
			cout << "\n\t [!] client not added becuz account number is used. \n\n";
			break;

		case clsBankClient::enSaveResults::svFaildEmptyObject:
			cout << "\n\t [!] client not added becuz client is empty. \n\n";
			break;

		}

	}



};

