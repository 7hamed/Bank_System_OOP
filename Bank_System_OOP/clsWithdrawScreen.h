#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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
	static void showWithdrawScreen()
	{
		_printScreenHeader("Withdraw Screen");

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

		double withdrawAmount = 0;
		cout << "\nenter withdraw amount : ";
		withdrawAmount = clsInputValidate::readDblNumber();

		char answer = 'n';
		cout << "\ndo u want to deposite [" << withdrawAmount << "] to this client [y-YES | n-NO] : ";
		cin >> answer;

		if (toupper(answer) == 'Y')
		{
			if(client1.withdraw(withdrawAmount))
			{
				cout << "\n\t [Withdraw Perform Successfully] \n";

				cout << "\n\t [*] new balance = " << client1.Balance << endl;
			}
			else
			{
				cout << "\n\t [!] withdraw not perform becuz amount bigger than balance.";
				cout << "\n\t       - withdraw amount = " << withdrawAmount;
				cout << "\n\t       - current balance = " << client1.Balance << endl;
			}
		}
		else
		{
			cout << "\n\t [!] Withdraw canseled. \n";
		}
	}

};
