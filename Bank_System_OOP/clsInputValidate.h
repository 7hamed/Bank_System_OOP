#pragma once

#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidate
{
public:

	static bool isNumberBetween(int theNumber, int from, int to)
	{
		return (theNumber >= from && theNumber <= to);
	}

	static bool isNumberBetween(double theNumber, double from, double to)
	{
		return (theNumber >= from && theNumber <= to);
	}

	static bool isNumberBetween(short theNumber, short from, short to)
	{
		return (theNumber >= from && theNumber <= to);
	}

	static bool isNumberBetween(float theNumber, float from, float to)
	{
		return (theNumber >= from && theNumber <= to);
	}

	static bool isDateBetween(clsDate theDate, clsDate from, clsDate to)
	{
		if (from.isDateAfterDate2(to))
			clsDate::swapDates(from, to);

		return (theDate.isDateAfterDate2(from) || theDate.isDateEqualDate2(from)
			&&
			theDate.isDateBeforeDate2(to) || theDate.isDateEqualDate2(to));

	}


	static string readString()
	{
		string input = "";

		getline(cin >> ws, input);

		return input;
	}

	static int readIntNumber(string invalidMessage = "invalid number, enter again : ")
	{
		int number = 0;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << invalidMessage;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return number;
	}

	static double readDblNumber(string invalidMessage = "invalid number, enter again : ")
	{
		double number = 0;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << invalidMessage;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return number;
	}

	static short readShortNumber(string invalidMessage = "invalid number, enter again : ")
	{
		short number = 0;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << invalidMessage;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return number;
	}

	static float readFloatNumber(string invalidMessage = "invalid number, enter again : ")
	{
		float number = 0;

		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << invalidMessage;
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		return number;
	}



	static int readIntNumberBetween(int from, int to, string invalidMessage = "number is not within range, enter again : ")
	{
		int number = readIntNumber();
		
		while (!isNumberBetween(number, from, to))
		{
			cout << invalidMessage;
			number = readIntNumber();
		}

		return number;
	}

	static double readDblNumberBetween(double from, double to, string invalidMessage = "number is not within range, enter again : ")
	{
		double number = readDblNumber();

		while (!isNumberBetween(number, from, to))
		{
			cout << invalidMessage;
			number = readDblNumber();
		}

		return number;
	}

	static short readShortNumberBetween(short from, short to, string invalidMessage = "number is not within range, enter again : ")
	{
		short number = readShortNumber();

		while (!isNumberBetween(number, from, to))
		{
			cout << invalidMessage;
			number = readShortNumber();
		}

		return number;
	}

	static float readFloatNumberBetween(float from, float to, string invalidMessage = "number is not within range, enter again : ")
	{
		float number = readFloatNumber();

		while (!isNumberBetween(number, from, to))
		{
			cout << invalidMessage;
			number = readFloatNumber();
		}

		return number;
	}


	static bool isValidDate(clsDate date)
	{
		return date.isValidDate();
	}

};

