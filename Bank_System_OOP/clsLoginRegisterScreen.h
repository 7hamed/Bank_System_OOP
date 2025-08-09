#pragma once
#include <iostream>
#include <vector>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"

using namespace std;

class clsLoginRegisterScreen : protected clsScreen
{
private:

	static void _printLoginRegisterRecordLine(clsUser::stLoginRegisterRecord record)
	{
		cout << "| " << setw(35) << left << record.LoginDateTime;
		cout << "| " << setw(15) << left << record.UserName;
		cout << "| " << setw(15) << left << record.Password;
		cout << "| " << setw(5) << left << record.Permissions;
	}


public:
	static void showLoginRegisterScreen()
	{
		if (!clsScreen::_checkAccessRights(clsUser::enPermission::pLoginRegister))
		{
			return;
		}
		
		vector<clsUser::stLoginRegisterRecord> vLoginRegisters = clsUser::getLoginRegisterListFromFile();
		
		string subtitle = to_string(vLoginRegisters.size()) + " Record(s)";

		_printScreenHeader("Login Register Screen", subtitle);

		cout << "\n_____________________________________________________________________________________\n";
		cout << "| " << setw(35) << left << "Date & Time";
		cout << "| " << setw(15) << left << "UserName";
		cout << "| " << setw(15) << left << "Password";
		cout << "| " << setw(5) << left << "Permissions";
		cout << "\n_____________________________________________________________________________________\n";

		if (vLoginRegisters.size() == 0)
		{
			cout << "\n   no Login Register Data avaliable in system \n";
		}
		else
		{
			for (clsUser::stLoginRegisterRecord r : vLoginRegisters)
			{
				_printLoginRegisterRecordLine(r);
				cout << endl;
			}
		}

		cout << "_____________________________________________________________________________________\n";

	}
};

