#pragma once
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"

class clsClientListScreen : protected clsScreen
{
	
private:
	static void _printClientRecordLine(clsBankClient client)
	{
		cout << "| " << setw(18) << left << client.AccountNumber();
		cout << "| " << setw(30) << left << client.fullName();
		cout << "| " << setw(15) << left << client.Phone;
		cout << "| " << setw(30) << left << client.Email;
		cout << "| " << setw(10) << left << client.PinCode;
		cout << "| " << setw(10) << left << client.Balance;
	}

public:
	static void showClientListScreen()
	{
		
		if (!_checkAccessRights(clsUser::enPermission::pClientList))
		{
			return;
		}
		
		
		vector<clsBankClient> vClients = clsBankClient::getClientsList();

		string title = "All Client List";
		string subtitle = "Client List(" + to_string(vClients.size()) + ") Client(s)";

		_printScreenHeader(title, subtitle);

		cout << "\t\t\t\t\t \n";
		
		cout << "\n________________________________________________________________________________";
		cout << "____________________________________________\n";
		cout << "| " << setw(18) << left << "Account Number";
		cout << "| " << setw(30) << left << "Client Name";
		cout << "| " << setw(15) << left << "Phone";
		cout << "| " << setw(30) << left << "Email";
		cout << "| " << setw(10) << left << "Pin Code";
		cout << "| " << setw(10) << left << "Balance";
		cout << "\n________________________________________________________________________________";
		cout << "____________________________________________\n";

		if (vClients.size() == 0)
		{
			cout << "\n   no client avaliable in system \n\n";
		}
		else
		{
			for (clsBankClient client : vClients)
			{
				_printClientRecordLine(client);
				cout << endl;
			}
		}

		cout << "________________________________________________________________________________";
		cout << "____________________________________________\n";
	}

};

