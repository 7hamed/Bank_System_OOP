#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalanceScreen : protected clsScreen
{
private:
	static void _printClientRecordLine(clsBankClient client)
	{
		cout << "| " << setw(18) << left << client.AccountNumber();
		cout << "| " << setw(40) << left << client.fullName();
		cout << "| " << setw(10) << left << client.Balance;
	}


public:
	static void showTotalBalanceScreen()
	{
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string subtitle = "(" + to_string(vClients.size()) + ") Clients";
		_printScreenHeader("Total Balance", subtitle);

		cout << "\n__________________________________________________________________________\n";
		cout << "| " << setw(18) << left << "Account Number";
		cout << "| " << setw(40) << left << "Client Name";
		cout << "| " << setw(10) << left << "Balance";
		cout << "\n___________________________________________________________________________\n";

		if (vClients.size() == 0)
		{
			cout << "\n   no client avaliable in system \n";
		}
		else
		{
			for (clsBankClient c : vClients)
			{
				_printClientRecordLine(c);
				cout << endl;
			}
		}

		cout << "___________________________________________________________________________\n";

		double totalBalance = clsBankClient::getTotalBalance();
		cout << setw(48) << left << "" << "Total Balance = " << totalBalance << endl;
		cout << "\t\t (" << clsUtil::numberToText((int)totalBalance) << ") \n";


	}


};

