#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"

//screens
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionMenu : protected clsScreen
{
private:
	enum enTransactionOption {Deposit = 1, Withdraw = 2, TotalBalance = 3, Transfer = 4, TransferLog = 5, ShowMainMenu = 6};

	static void _backToTransactionMenu()
	{
		cout << "\n\n press any key to back to transaction menu...";
		system("pause>0");

		showTransactionMenu();
	}

	static short _readTransactionMenuOption()
	{
		short choice = 0;
		cout << "\nchoose option number [1-6] : ";
		choice = clsInputValidate::readShortNumberBetween(1, 6, "number is not within [1-6], choose again : ");

		return choice;
	}

	static void _showDepositScreen()
	{
		clsDepositScreen::showDepositScreen();
	}

	static void _showWithdrawScreen()
	{
		clsWithdrawScreen::showWithdrawScreen();
	}

	static void _showTotalBalanceScreen()
	{
		clsTotalBalanceScreen::showTotalBalanceScreen();
	}

	static void _showTransferScreen()
	{
		clsTransferScreen::showTransferScreen();
	}

	static void _showTransferLogScreen()
	{
		clsTransferLogScreen::showTransferLogScreen();
	}

	static void _performTransactionMenuOption(enTransactionOption option)
	{
		switch (option)
		{
		case enTransactionOption::Deposit:
			system("cls");
			_showDepositScreen();
			_backToTransactionMenu();
			break;

		case enTransactionOption::Withdraw:
			system("cls");
			_showWithdrawScreen();
			_backToTransactionMenu();
			break;

		case enTransactionOption::TotalBalance:
			system("cls");
			_showTotalBalanceScreen();
			_backToTransactionMenu();
			break;

		case enTransactionOption::Transfer:
			system("cls");
			_showTransferScreen();
			_backToTransactionMenu();
			break;

		case enTransactionOption::TransferLog:
			system("cls");
			_showTransferLogScreen();
			_backToTransactionMenu();
			break;

		case enTransactionOption::ShowMainMenu:
			// nothing 
			break;
		}
	}
	
public:
	static void showTransactionMenu()
	{
		if (!_checkAccessRights(clsUser::enPermission::pTransaction))
		{
			return;
		}
		
		system("cls");
		
		_printScreenHeader("Transaction Menu Screen");

		cout << clsUtil::tabs(3) << "=================================================\n";
		cout << clsUtil::tabs(3) << "                 Transaction Menu \n";
		cout << clsUtil::tabs(3) << "=================================================\n\n";

		cout << clsUtil::tabs(4) << "[1] Deposit" << endl;
		cout << clsUtil::tabs(4) << "[2] Withdraw" << endl;
		cout << clsUtil::tabs(4) << "[3] Total Balance" << endl;
		cout << clsUtil::tabs(4) << "[4] Transfer" << endl;
		cout << clsUtil::tabs(4) << "[5] Transfer Log" << endl;
		cout << clsUtil::tabs(4) << "[6] Main Menu" << "\n\n";

		cout << clsUtil::tabs(3) << "=================================================\n";

		_performTransactionMenuOption((enTransactionOption)_readTransactionMenuOption());
	}

};

