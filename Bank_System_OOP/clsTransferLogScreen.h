#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransferLogScreen : protected clsScreen
{
private:
	static void _printTransferRecord(clsBankClient::stTransferRecord record)
	{
		cout << "| " << setw(20) << left << record.dateAndTime;
		cout << "| " << setw(6) << left << record.sourceClient;
		cout << "| " << setw(6) << left << record.destinationClient;
		cout << "| " << setw(10) << left << record.transferAmount;
		cout << "| " << setw(10) << left << record.sourceNewBalance;
		cout << "| " << setw(10) << left << record.destinationNewBalance;
		cout << "| " << setw(12) << left << record.userNameDoer;
	}


public:
	static void showTransferLogScreen()
	{
		vector<clsBankClient::stTransferRecord> vTransferRecord = clsBankClient::getTransferList();
		
		string subtitle = "(" + to_string(vTransferRecord.size()) + ") Recod(s)";
		_printScreenHeader("Transfer Log Screen", subtitle);

		cout << "\n_________________________________________________________________________________\n";
		cout << "| " << setw(20) << left << "Date and Time";
		cout << "| " << setw(6) << left << "s.acc";
		cout << "| " << setw(6) << left << "d.acc";
		cout << "| " << setw(10) << left << "Amount";
		cout << "| " << setw(10) << left << "s.Balance";
		cout << "| " << setw(10) << left << "d.Balance";
		cout << "| " << setw(12) << left << "User";
		cout << "\n_________________________________________________________________________________\n";

		if (vTransferRecord.size() == 0)
		{
			cout << "\n   no Transfer Log avaliable in system \n";
		}
		else
		{
			for (clsBankClient::stTransferRecord r : vTransferRecord)
			{
				_printTransferRecord(r);
				cout << endl;
			}
		}
		cout << "_________________________________________________________________________________\n";

		
	}
};

