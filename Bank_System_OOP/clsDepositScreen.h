#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositScreen : protected clsScreen
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
	static void showDepositScreen()
	{
		_printScreenHeader("Depoist Screen");

		string accNumber = "";
		cout << "enter account number : ";
		accNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accNumber))
		{
			cout << "account number not found, enter another one : ";
			accNumber = clsInputValidate::readString();
		}

		clsBankClient client1 = clsBankClient::find(accNumber);

		_printClient(client1);

		double depositAmount = 0;
		cout << "\nenter deposit amount : ";
		depositAmount = clsInputValidate::readDblNumber();

		char answer = 'n';
		cout << "\ndo u want to deposite [" << depositAmount << "] to this client [y-YES | n-NO] : ";
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			client1.deposit(depositAmount);

			cout << "\n\t [Deposit Perform Successfully] \n";

			cout << "\n\t [*] new balance = " << client1.Balance << endl;
		}
		else
		{
			cout << "\n\t [!] Deposit canseled. \n";
		}

	}


};

