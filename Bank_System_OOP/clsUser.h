#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;

class clsUser : public clsPerson
{
private:
	struct stLoginRegisterRecord;
	enum enMode { EmptyMode = 1, UpdateMode = 2, AddNewMode = 3 };

	enMode _mode;
	string _userName;
	string _password;
	int _permission;
	bool _markToDelete = false;


	static clsUser _getEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsUser _convertLineToUserObject(string dataLine)
	{
		vector<string> values = clsString::split(dataLine, "#//#");

		string originalPassword = clsUtil::decryptionText(values[5]);

		return clsUser(enMode::UpdateMode, values[0], values[1], values[2],
			values[3], values[4], originalPassword, stoi(values[6]));
	}

	static vector<clsUser> _loadUsersDataFromFile()
	{
		vector<clsUser> vUsers;

		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			clsUser tempUser = _getEmptyUserObject();
			while (getline(myFile, line))
			{
				tempUser = _convertLineToUserObject(line);
				vUsers.push_back(tempUser);
			}

			myFile.close();
		}

		return vUsers;
	}


	static string _convertUserObjectToLine(clsUser user, string delimiter = "#//#")
	{
		string encryptionPassword = clsUtil::encryptionText(user.Password);
		
		string line = user.FirstName + delimiter;
		line += user.LastName + delimiter;
		line += user.Email + delimiter;
		line += user.Phone + delimiter;
		line += user.UserName + delimiter;
		line += encryptionPassword + delimiter;
		line += to_string(user.Permission);

		return line;
	}

	static void _saveUsersDataToFile(vector<clsUser> vUsers)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out);

		if (myFile.is_open())
		{
			string line = "";
			for (clsUser u : vUsers)
			{
				if(u._markToDelete == false)
				{
					line = _convertUserObjectToLine(u);
					myFile << line << endl;
				}
			}
		}

		myFile.close();
	}

	void _update()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& u : vUsers)
		{
			if (u.UserName == this->UserName)
			{
				u = *this;
				break;
			}
		}

		_saveUsersDataToFile(vUsers);
	}

	static void _addDataLineToFile(string line)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << line << endl;
			myFile.close();
		}
	}

	void _addNew()
	{
		_addDataLineToFile(_convertUserObjectToLine(*this));
	}

	string _prepareLoginRecord(string delimiter = "#//#")
	{
		string line = clsDate::getSystemDateTimeString() + delimiter;
		line += UserName + delimiter;
		line += clsUtil::encryptionText(Password) + delimiter;
		line += to_string(Permission);

		return line;
	}

	static stLoginRegisterRecord _ConvertlineToLoginRegisterStruct(string dataLine, string delimiter = "#//#")
	{
		vector<string> vData = clsString::split(dataLine, delimiter);

		stLoginRegisterRecord record;
		record.LoginDateTime = vData[0];
		record.UserName = vData[1];
		record.Password = clsUtil::decryptionText(vData[2]);
		record.Permissions = stoi(vData[3]);

		return record;
	}

public:

	enum enPermission {pAll = -1, pClientList = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, 
		pFindClient = 16, pTransaction = 32, pManageUser = 64, pLoginRegister = 128};
	
	struct stLoginRegisterRecord
	{
		string LoginDateTime;
		string UserName;
		string Password;
		int Permissions;
	};

	clsUser(enMode mode, string firstName, string lastName, string email, string phone, 
		string userName, string password, int permission)
		: clsPerson(firstName, lastName, email, phone)
	{
		_mode = mode;
		_userName = userName;
		_password = password;
		_permission = permission;
	}

	void setUserName(string value)
	{
		_userName = value;
	}
	string getUserName()
	{
		return _userName;
	}
	__declspec(property(get = getUserName, put = setUserName)) string UserName;

	void setPassword(string value)
	{
		_password = value;
	}
	string getPassword()
	{
		return _password;
	}
	__declspec(property(get = getPassword, put = setPassword)) string Password;

	void setPermission(int value)
	{
		_permission = value;
	}
	int getPermission()
	{
		return _permission;
	}
	__declspec(property(get = getPermission, put = setPermission)) int Permission;




	static clsUser find(string userName)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			clsUser tempUser = _getEmptyUserObject();

			while (getline(myFile, line))
			{
				tempUser = _convertLineToUserObject(line);
				if (tempUser.UserName == userName)
				{
					myFile.close();
					return tempUser;
				}
			}
		}
		
		myFile.close();
		return _getEmptyUserObject();
	}

	static clsUser find(string userName, string password)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			clsUser tempUser = _getEmptyUserObject();

			while (getline(myFile, line))
			{
				tempUser = _convertLineToUserObject(line);
				if (tempUser.UserName == userName && tempUser.Password == password)
				{
					myFile.close();
					return tempUser;
				}
			}
		}

		myFile.close();
		return _getEmptyUserObject();
	}

	bool isEmpty()
	{
		return (_mode == enMode::EmptyMode);
	}

	static bool isUserExist(string userName)
	{
		clsUser user = find(userName);

		return !(user.isEmpty());
	}

	static clsUser getAddNewUserObject(string userName)
	{
		return clsUser(enMode::AddNewMode, "", "", "", "", userName, "", -1);
	}

	enum enSaveResult { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

	enSaveResult save()
	{
		switch (_mode)
		{
		case enMode::EmptyMode:
			return enSaveResult::svFaildEmptyObject;
			break;

		case enMode::UpdateMode:
			_update();
			return enSaveResult::svSucceeded;
			break;

		case enMode::AddNewMode:
			if (isUserExist(_userName))
			{
				return svFaildUserExists;
			}
			else
			{
				_addNew();
				return enSaveResult::svSucceeded;
			}
			break;
		}
	}

	bool Delete()
	{
		vector<clsUser> vUsers = _loadUsersDataFromFile();

		for (clsUser& u : vUsers)
		{
			if (u.UserName == UserName)
			{
				u._markToDelete = true;
				_saveUsersDataToFile(vUsers);
				*this = _getEmptyUserObject();

				return true;
			}
		}

		return false;
	}

	static vector<clsUser> getUserList()
	{
		return _loadUsersDataFromFile();
	}


	bool checkAccessPermission(enPermission permission)
	{
		if (this->Permission == enPermission::pAll)
		{
			return true;
		}

		if ((this->Permission & permission) == permission)
		{
			return true;
		}
		
		return false;
	}

	void registerLogin()
	{
		string dataLine = _prepareLoginRecord();

		fstream myFile;
		myFile.open("LoginRegisters.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;
			myFile.close();
		}
	}

	static vector<stLoginRegisterRecord> getLoginRegisterListFromFile()
	{
		vector<stLoginRegisterRecord> vLoginRegisters;

		fstream myFile;
		myFile.open("LoginRegisters.txt", ios::in);

		if (myFile.is_open())
		{
			string line = "";
			stLoginRegisterRecord tempRegisterData;

			while (getline(myFile, line))
			{
				tempRegisterData = _ConvertlineToLoginRegisterStruct(line);

				vLoginRegisters.push_back(tempRegisterData);
			}

			myFile.close();
		}

		return vLoginRegisters;
	}

};

