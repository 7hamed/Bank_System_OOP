#pragma once

#include <iostream>
#include "clsUtil.h"
#include "clsUser.h"
#include "clsDate.h"
#include "clsGlobal.h"

using namespace std;

class clsScreen
{
private:

	static string _setwCenter(short placeNumber, string theWord)
	{
		short center = (placeNumber / 2) - (theWord.length() / 2);
		string space = "";

		for (short i = 0; i < center; i++)
			space += " ";

		return space;
		
	}


protected:
	static void _printScreenHeader(string title, string subtitle = "")
	{



		cout << endl << clsUtil::tabs(3) << "-------------------------------------------------\n";
		
		cout << clsUtil::tabs(3) << _setwCenter(50, title) << title;

		if (subtitle != "")
		{
			cout << endl << clsUtil::tabs(3) << _setwCenter(50, subtitle) << subtitle;
		}

		cout << endl << clsUtil::tabs(3) << "-------------------------------------------------\n\n";

		cout << clsUtil::tabs(3) << "User : " << CurrentUser.UserName << endl;
		cout << clsUtil::tabs(3) << "Date : " << clsDate::toString(clsDate()) << "\n\n";

	}

	static bool _checkAccessRights(clsUser::enPermission permission)
	{
		if (!CurrentUser.checkAccessPermission(permission))
		{
			_printScreenHeader("Access Denied! , contact your Admin.");
			return false;
		}
		else
		{
			return true;
		}
	}

};

