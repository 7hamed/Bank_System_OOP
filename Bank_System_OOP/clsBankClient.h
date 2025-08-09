#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
	struct stTransferRecord;
	enum enMode { emptyMode = 1, updateMode = 2, addNewMode = 3 };

	enMode _mode;
	string _accountNumber;
	string _pinCode;
	double _balance;
	bool _markToDelete = false;


	static clsBankClient _convertLineToClientObject(string line)
	{
		vector<string> values = clsString::split(line, "#//#");

		return clsBankClient(enMode::updateMode, values[0], values[1], values[2],
			values[3], values[4], values[5], stod(values[6]));
	}

	static clsBankClient _getEmptyClientObject()
	{
		return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _loadClientsDataFromFile()
	{
		vector<clsBankClient> vClients;

		fstream myFile;
		myFile.open("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			clsBankClient client = _getEmptyClientObject();

			while (getline(myFile, line))
			{
				client = _convertLineToClientObject(line);
				vClients.push_back(client);
			}

			myFile.close();
		}

		return vClients;
	}

	static string _convertClientObjectToLine(clsBankClient client, string delimiter = "#//#")
	{
		string line = client.FirstName + delimiter;
		line += client.LastName + delimiter;
		line += client.Email + delimiter;
		line += client.Phone + delimiter;
		line += client.AccountNumber() + delimiter;
		line += client.PinCode + delimiter;
		line += to_string(client.Balance);

		return line;
	}

	static void _saveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out);

		if (myFile.is_open())
		{
			string line = "";
			for (clsBankClient c : vClients)
			{
				if(c._markToDelete == false)
				{
					line = _convertClientObjectToLine(c);
					myFile << line << endl;
				}
			}

			myFile.close();
		}

		return;
	}

	void _update()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == this->AccountNumber())
			{
				c = *this;
				break;
			}
		}

		_saveClientsDataToFile(vClients);
	}

	void _addDataLineToFile(string dataLine)
	{
		fstream myFile;
		myFile.open("Clients.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;
			
			myFile.close();
		}

		return;
	}
	
	void _addNew()
	{
		_addDataLineToFile(_convertClientObjectToLine(*this));
	}

	string _prepareTransferRecord(clsBankClient destinationClient, double transferAmount, string userName, string delimiter = "#//#")
	{
		return clsDate::getSystemDateTimeString() + delimiter +
			this->AccountNumber() + delimiter +
			destinationClient.AccountNumber() + delimiter +
			to_string(transferAmount) + delimiter +
			to_string(this->Balance) + delimiter +
			to_string(destinationClient.Balance) + delimiter +
			userName;

	}

	void _transferLog(clsBankClient destinationClient, double transferAmount, string userName)
	{
		string dataLine = _prepareTransferRecord(destinationClient, transferAmount, userName);

		fstream myFile;
		myFile.open("Transfers.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;
			myFile.close();
		}

	}


	static stTransferRecord _convertLineToTransferRecord(string dataLine)
	{
		vector<string> data = clsString::split(dataLine, "#//#");
		stTransferRecord record;

		record.dateAndTime = data[0];
		record.sourceClient = data[1];
		record.destinationClient = data[2];
		record.transferAmount = stod(data[3]);
		record.sourceNewBalance = stod(data[4]);
		record.destinationNewBalance = stod(data[5]);
		record.userNameDoer = data[6];

		return record;
	}

public:
	clsBankClient(enMode mode, string fName, string lName, string email, string phone,
		string account, string pinCode, double balance) : clsPerson(fName, lName, email, phone)
	{
		_mode = mode;
		_accountNumber = account;
		_pinCode = pinCode;
		_balance = balance;
	}

	struct stTransferRecord
	{
		string dateAndTime;
		string sourceClient;
		string destinationClient;
		double transferAmount = 0;
		double sourceNewBalance = 0;
		double destinationNewBalance = 0;
		string userNameDoer;
	};

	// AccountNumber property (read only)
	string AccountNumber()
	{
		return _accountNumber;
	}
	

	// PinCode property
	string getPinCode()
	{
		return _pinCode;
	}
	void setPinCode(string value)
	{
		_pinCode = value;
	}
	_declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	// Balance property
	double getBalance()
	{
		return _balance;
	}
	void setBalance(double value)
	{
		_balance = value;
	}
	_declspec(property(get = getBalance, put = setBalance)) double Balance;


	/*	no ui related in client object
	
	void print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;
		cout << "\nLastName    : " << LastName;
		cout << "\nFull Name   : " << fullName();
		cout << "\nEmail       : " << Email;
		cout << "\nPhone       : " << Phone;
		cout << "\nAcc. Number : " << AccountNumber();
		cout << "\nPassword    : " << PinCode;
		cout << "\nBalance     : " << Balance;
		cout << "\n___________________\n";
	}*/

	string fullName()
	{
		return FirstName + " " + LastName;
	}

	double isEmpty()
	{
		return _mode == enMode::emptyMode;
	}

	static clsBankClient find(string accountNumber)
	{
		fstream myFile("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				if (accountNumber == client.AccountNumber())
				{
					myFile.close();
					return client;
				}
			}

			return _getEmptyClientObject();
		}
	}

	static clsBankClient find(string accountNumber, string pinCode)
	{
		fstream myFile("Clients.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			while (getline(myFile, line))
			{
				clsBankClient client = _convertLineToClientObject(line);
				if (accountNumber == client.AccountNumber() && pinCode == client.PinCode)
				{
					myFile.close();
					return client;
				}
			}

			return _getEmptyClientObject();
		}
	}

	static bool isClientExist(string accountNumber)
	{
		clsBankClient client = find(accountNumber);

		return !client.isEmpty();
	}


	static clsBankClient getAddNewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0.0);
	}


	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExist = 2};

	enSaveResults save()
	{
		switch (_mode)
		{
		case clsBankClient::emptyMode:
		{
			return enSaveResults::svFaildEmptyObject;
			break;
		}
		case clsBankClient::updateMode:
		{
			_update();

			return enSaveResults::svSucceeded;
			break;
		}
		case clsBankClient::addNewMode:
		{
			if (isClientExist(_accountNumber))
			{
				return enSaveResults::svFaildAccountNumberExist;
			}
			else
			{
				_addNew();
				_mode = enMode::updateMode;

				return enSaveResults::svSucceeded;
			} 
		}

		default:
			break;
		}
	}


	bool Delete()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();

		for (clsBankClient& c : vClients)
		{
			if (c.AccountNumber() == _accountNumber)
			{
				c._markToDelete = true;
				_saveClientsDataToFile(vClients);

				*this = _getEmptyClientObject();

				return true;
			}
		}

		return false;
		
	}

	static vector<clsBankClient> getClientsList()
	{
		return _loadClientsDataFromFile();
	}

	static double getTotalBalance()
	{
		vector<clsBankClient> vClients = _loadClientsDataFromFile();
		double totalBalance = 0;

		for (clsBankClient client : vClients)
		{
			totalBalance += client.Balance;
		}

		return totalBalance;
	}

	void deposit(double amount)
	{
		_balance += amount;

		save();
	}

	bool withdraw(double amount)
	{
		if (amount > _balance)
		{
			return false;
		}
		else
		{
			_balance -= amount;
			save();
			return true;
		}
	}

	bool transferTo(clsBankClient& destinationClient, double amount, string userName)
	{
		if (amount > this->Balance || this->_accountNumber == destinationClient._accountNumber || amount < 0)
		{
			return false;
		}
		else
		{
			this->withdraw(amount);
			destinationClient.deposit(amount);
			this->_transferLog(destinationClient, amount, userName);
			return true;
		}
	}

	static vector<stTransferRecord> getTransferList()
	{
		vector<stTransferRecord> vTransferRecord;

		fstream myFile;
		myFile.open("Transfers.txt", ios::in);

		if (myFile.is_open())
		{
			string dataLine = "";
			stTransferRecord tempRecord;

			while (getline(myFile, dataLine))
			{
				tempRecord = _convertLineToTransferRecord(dataLine);
				vTransferRecord.push_back(tempRecord);
			}

			myFile.close();
		}

		return vTransferRecord;
	}

};

