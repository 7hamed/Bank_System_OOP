#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
	static void _printClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << client.fullName();
		cout << "\nAcc. Number : " << client.AccountNumber();
		cout << "\nBalance     : " << client.Balance;
		cout << "\n___________________\n";
	}

public:
	static void showTransferScreen()
	{
		_printScreenHeader("Transfer Screen");

		string accNumberFrom = "";
		string accNumberTo = "";

		cout << "enter account number to Transfer From : ";
		accNumberFrom = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accNumberFrom))
		{
			cout << "account number not found. enter another to Transfer From : ";
			accNumberFrom = clsInputValidate::readString();
		}
		clsBankClient client1 = clsBankClient::find(accNumberFrom);
		_printClient(client1);


		cout << "\n\nenter account number to Transfer To : ";
		accNumberTo = clsInputValidate::readString();
		while (!clsBankClient::isClientExist(accNumberTo))
		{
			cout << "account number not found. enter another to Transfer To : ";
			accNumberTo = clsInputValidate::readString();
		}
		clsBankClient client2 = clsBankClient::find(accNumberTo);
		_printClient(client2);
		
		
		double transferAmount = 0;
		cout << "\n\nenter transfer amount : ";
		transferAmount = clsInputValidate::readDblNumber();

		while (transferAmount > client1.Balance)
		{
			cout << "amount bigger than balance,enter another transfer amount : ";
			transferAmount = clsInputValidate::readDblNumber();
		}

		char answer = 'n';
		cout << "do u want to perform [ " << transferAmount << " ] transfer [y-YES | n-NO] : ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			if (client1.transferTo(client2, transferAmount, CurrentUser.UserName))
			{
				cout << "\n\t [Transfer Done Successfully] \n";
				
				_printClient(client1);
				cout << endl;
				_printClient(client2);
			}
			else
			{
				cout << "\n\t [!] ERROR happen, Transfer not perform. \n";
			}
		}
		else
		{
			cout << "\n\t [!] Transfer Canceled. \n";
		}
	}


};

