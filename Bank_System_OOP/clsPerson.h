#pragma once
#include <iostream>
#include "InterfaceCommunication.h"

using namespace std;

class clsPerson : public InterfaceCommunication
{
private:
	string _firstName;
	string _lastName;
	string _Email;
	string _phone;

public:
	clsPerson(string firstName, string lastName, string email, string phone)
	{
		_firstName = firstName;
		_lastName = lastName;
		_Email = email;
		_phone = phone;
	}

	// FirstName property
	string getFirstName()
	{
		return _firstName;
	}
	void setFirstName(string value)
	{
		_firstName = value;
	}
	_declspec(property(get = getFirstName, put = setFirstName)) string FirstName;

	// LastName property
	string getLastName()
	{
		return _lastName;
	}
	void setLastName(string value)
	{
		_lastName = value;
	}
	__declspec(property(get = getLastName, put = setLastName)) string LastName;

	// Email Property
	string getEmail()
	{
		return _Email;
	}
	void setEmail(string value)
	{
		_Email = value;
	}
	__declspec(property(get = getEmail, put = setEmail)) string Email;

	// Phone Property
	string getPhone()
	{
		return _phone;
	}
	void setPhone(string value)
	{
		_phone = value;
	}
	__declspec(property(get = getPhone, put = setPhone)) string Phone;


	string fullName()
	{
		return _firstName + " " + _lastName;
	}


	// interface communication
	void sendEmail(string title, string body)
	{

	}

	void sendFax(string title, string body)
	{

	}

	void sendSMS(string title, string body)
	{

	}
};

