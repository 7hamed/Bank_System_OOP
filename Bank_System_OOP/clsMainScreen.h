#pragma once

#include <iostream>
#include "clsUtil.h"
#include "clsGlobal.h"

// screens
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFIndClientScreen.h"
#include "clsTransactionMenu.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegisterScreen.h"

using namespace std;

class clsMainScreen : protected clsScreen
{

private:
	enum enMainOption {
		ShowClientList = 1, AddClient = 2, DeleteClient = 3, UpdateClient = 4,
		FindClient = 5, TransactionMenu = 6, ManageUsers = 7, LoginRegister = 8, ExitMain = 9
	};

	static void _backToMainMenu()
	{
		cout << "\n\n press any key to back to main menu...";
		system("pause>0");

		showMainMenu();
	}

	static void _showAllClientsScreen()
	{
		clsClientListScreen::showClientListScreen();
	}

	static void _addClientScreen()
	{
		clsAddNewClientScreen::showAddNewClientScreen();
	}

	static void _deleteClientScreen()
	{
		clsDeleteClientScreen::showDeleteClientScreen();
	}

	static void _updateClientScreen()
	{
		clsUpdateClientScreen::showUpdateClientScreen();
	}

	static void _findClientScreen()
	{
		clsFIndClientScreen::showFindClientScreen();
	}

	static void _showTransactionMenuScreen()
	{
		clsTransactionMenu::showTransactionMenu();
	}

	static void _showManageUsersScreen()
	{
		clsManageUsersScreen::showManageUsersScreen();
	}

	static void _showLoginRegisterScreen()
	{
		clsLoginRegisterScreen::showLoginRegisterScreen();
	}

	static void _logout()
	{
		CurrentUser = clsUser::find("", "");

		// do nothing
	}

	static void _performMainMenuOption(enMainOption option)
	{
		switch (option)
		{
		case enMainOption::ShowClientList:
			system("cls");
			_showAllClientsScreen();
			_backToMainMenu();
			break;

		case enMainOption::AddClient:
			system("cls");
			_addClientScreen();
			_backToMainMenu();
			break;

		case enMainOption::DeleteClient:
			system("cls");
			_deleteClientScreen();
			_backToMainMenu();
			break;

		case enMainOption::UpdateClient:
			system("cls");
			_updateClientScreen();
			_backToMainMenu();
			break;

		case enMainOption::FindClient:
			system("cls");
			_findClientScreen();
			_backToMainMenu();
			break;

		case enMainOption::TransactionMenu:
			system("cls");
			_showTransactionMenuScreen();
			_backToMainMenu();
			break;

		case enMainOption::ManageUsers:
			system("cls");
			_showManageUsersScreen();
			_backToMainMenu();
			break;

		case enMainOption::LoginRegister:
			system("cls");
			_showLoginRegisterScreen();
			_backToMainMenu();
			break;

		case enMainOption::ExitMain:
			system("cls");
			_logout();
			break;

		}
	}

	static short _readMainMenuOption()
	{
		short choice = 0;
		cout << "\nchoose option number [1-9] : ";
		choice = clsInputValidate::readShortNumberBetween(1, 9, "number is not within [1-9], choose again : ");

		return choice;
	}

public:
	static void showMainMenu()
	{
		
		system("cls");

		_printScreenHeader("Main Menu Screen");

		cout << clsUtil::tabs(3) << "=================================================\n";
		cout << clsUtil::tabs(3) << "                     Main Menu \n";
		cout << clsUtil::tabs(3) << "=================================================\n\n";

		cout << clsUtil::tabs(4) << "[1] Show Client List" << endl;
		cout << clsUtil::tabs(4) << "[2] Add Client" << endl;
		cout << clsUtil::tabs(4) << "[3] Delete Client" << endl;
		cout << clsUtil::tabs(4) << "[4] Update Client" << endl;
		cout << clsUtil::tabs(4) << "[5] Find Client" << endl;
		cout << clsUtil::tabs(4) << "[6] Transaction Menu" << endl;
		cout << clsUtil::tabs(4) << "[7] Manage Users" << endl;
		cout << clsUtil::tabs(4) << "[8] Login Registers" << endl;
		cout << clsUtil::tabs(4) << "[9] Logout" << "\n\n";
		
		cout << clsUtil::tabs(3) << "=================================================\n";

		_performMainMenuOption((enMainOption)_readMainMenuOption());
	}

};

