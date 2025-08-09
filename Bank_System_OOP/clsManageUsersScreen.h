#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"

// screens
#include "clsUserListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
	enum enManageUsersOption { ShowUserList = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4, FindUser = 5, ShowMainMenu = 6};

	static void _backToManageUsersScreen()
	{
		cout << "\n\n press any key to back to Manage Users menu...";
		system("pause>0");

		showManageUsersScreen();
	}

	static short _readManageUsersScreenOption()
	{
		short choice = 0;
		cout << "\nchoose option number [1-6] : ";
		choice = clsInputValidate::readShortNumberBetween(1, 8, "number is not within [1-6], choose again : ");

		return choice;
	}

	static void _showUsersListScreen()
	{
		clsUserListScreen::showUserListScreen();
	}

	static void _showAddNewUserScreen()
	{
		clsAddNewUserScreen::showAddNewUserScreen();
	}

	static void _showDeleteUserScreen()
	{
		clsDeleteUserScreen::showDeleteUserScreen();
	}

	static void _showUpdateUserScreen()
	{
		clsUpdateUserScreen::showUpdateUserScreen();
	}

	static void _showFindUserScreen()
	{
		clsFindUserScreen::showFindUserScreen();
	}

	static void _performManageUsersOption(enManageUsersOption option)
	{
		switch (option)
		{
		case enManageUsersOption::ShowUserList:
			system("cls");
			_showUsersListScreen();
			_backToManageUsersScreen();
			break;

		case enManageUsersOption::AddNewUser:
			system("cls");
			_showAddNewUserScreen();
			_backToManageUsersScreen();
			break;
		
		case enManageUsersOption::DeleteUser:
			system("cls");
			_showDeleteUserScreen();
			_backToManageUsersScreen();
			break;

		case enManageUsersOption::UpdateUser:
			system("cls");
			_showUpdateUserScreen();
			_backToManageUsersScreen();
			break;

		case enManageUsersOption::FindUser:
			system("cls");
			_showFindUserScreen();
			_backToManageUsersScreen();
			break;

		case enManageUsersOption::ShowMainMenu:
			// nothing
			break;
		}
	}

public:
	static void showManageUsersScreen()
	{
		
		
		if (!_checkAccessRights(clsUser::enPermission::pManageUser))
		{
			return;
		}
		
		system("cls");

		_printScreenHeader("Manage Users Screen");


		cout << clsUtil::tabs(3) << "=================================================\n";
		cout << clsUtil::tabs(3) << "                Manage Users Menu \n";
		cout << clsUtil::tabs(3) << "=================================================\n\n";

		cout << clsUtil::tabs(4) << "[1] Show Users List" << endl;
		cout << clsUtil::tabs(4) << "[2] Add User" << endl;
		cout << clsUtil::tabs(4) << "[3] Delete User" << endl;
		cout << clsUtil::tabs(4) << "[4] Update User" << endl;
		cout << clsUtil::tabs(4) << "[5] Find User" << endl;
		cout << clsUtil::tabs(4) << "[6] Main Menu" << "\n\n";

		cout << clsUtil::tabs(3) << "=================================================\n";


		_performManageUsersOption((enManageUsersOption)_readManageUsersScreenOption());
	}



};

