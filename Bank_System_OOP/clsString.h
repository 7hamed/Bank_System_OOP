#pragma once // easy way to do work of Include Guards

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class clsString
{

private:
	string _value;

public: // _value property
	void setValue(string value)
	{
		this->_value = value;
	}
	string getValue()
	{
		return this->_value;
	}

	__declspec(property(get = getValue, put = setValue)) string Value; // property like C#


public: // constructors
	clsString()
	{
		this->_value = "";
	}

	clsString(string value) // overload parameterized constructor
	{
		this->Value = value; // use property in constructor
	}



public: // string functions

	static string trimLeft(string s)
	{
		short i = 0;
		while (s[i] == ' ')
			i++;

		return s.erase(0, i);
	}
	void trimLeft()
	{
		_value = trimLeft(_value);
	}


	static string trimRight(string s)
	{
		short i = (short)s.length() - 1;
		while (s[i] == ' ')
			i--;

		return s.erase(i + 1, s.length());
	}
	void trimRight()
	{
		_value = trimRight(_value);
	}


	static string trim(string s)
	{
		return trimLeft(trimRight(s));
	}
	void trim()
	{
		_value = trim(_value);
	}


	static string lowerAllString(string s)
	{
		for (short i = 0; i < s.length(); i++)
		{
			s[i] = tolower(s[i]);
		}

		return s;
	}
	void lowerAllString()
	{
		_value = lowerAllString(_value);
	}


	static string upperAllString(string s)
	{
		for (short i = 0; i < s.length(); i++)
		{
			s[i] = toupper(s[i]);
		}

		return s;
	}
	void upperAllString()
	{
		_value = upperAllString(_value);
	}


	static string replaceWordInString(string s, string stringToReplace, string replaceTo)
	{
		short pos = 0;
		while ((pos = s.find(stringToReplace)) != string::npos)
		{
			s.replace(pos, stringToReplace.length(), replaceTo);
			// replace [(int)index, (int)sizeof word, (string)new word]
		}

		return s;
	}
	void replaceWordInString(string stringToReplace, string replaceTo)
	{
		_value = replaceWordInString(_value, stringToReplace, replaceTo);
	}


	static vector<string> split(string s, string delimiter)
	{
		short pos = 0;
		string word = "";
		vector<string> vWords;

		while ((pos = s.find(delimiter)) != string::npos)
		{
			word = s.substr(0, pos);
			//if (word != "")
			//{
				vWords.push_back(word);
			//}

			s = s.erase(0, pos + delimiter.length());
		}

		// print the last word
		if (s != "")
		{
			vWords.push_back(s);
		}

		return vWords;
	}
	vector<string> split(string delimiter)
	{
		return split(_value, delimiter);
	}


	static string joinString(vector<string> vWords, string delimiter)
	{
		string line = "";

		for (string& word : vWords)
		{
			line = line + word + delimiter;
		}

		return line.substr(0, line.length() - delimiter.length());
	}


	static string joinString(string* s, short length, string delimiter)
	{
		string line = "";

		for (short i = 0; i < length; i++)
		{
			line = line + s[i] + delimiter;
		}

		return line.substr(0, line.length() - delimiter.length());
	}



	static string reverseWord(string s, string delimiter = " ")
	{
		string line = "";

		vector<string> vWords = clsString::split(s, delimiter);

		vector<string>::iterator iter = vWords.end(); // iter -> pointer of vecter
		while (iter != vWords.begin())
		{
			iter--;
			line = line + *iter + delimiter;
		}

		return line.substr(0, line.length() - delimiter.length());
	}
	string reverseWord(string delimiter = " ")
	{
		return reverseWord(_value, delimiter);
	}


	static string LowerFirstLetterOfEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ' && isFirstLetter)
			{
				Text[i] = char(tolower(Text[i]));
			}

			isFirstLetter = (Text[i] == ' ' ? true : false);
		}
		return Text;
	}
	void LowerFirstLetterOfEachWord()
	{
		_value = LowerFirstLetterOfEachWord(_value);
	}


	static string UpperFirstLetterOfEachWord(string Text)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ' && isFirstLetter)
			{
				Text[i] = char(toupper(Text[i]));
			}

			isFirstLetter = (Text[i] == ' ' ? true : false);
		}
		return Text;
	}
	void UpperFirstLetterOfEachWord()
	{
		_value = UpperFirstLetterOfEachWord(_value);
	}


	static string InvertAllLettersStrig(string Text)
	{
		bool isFirstLetter = true;

		for (int i = 0; i < Text.length(); i++)
		{
			if (Text[i] != ' ' && isFirstLetter)
			{
				Text[i] = (isupper(Text[i]) ? tolower(Text[i]) : toupper(Text[i]));
			}

			isFirstLetter = (Text[i] == ' ' ? true : false);
		}
		return Text;
	}
	void InvertAllLettersStrig()
	{
		_value = InvertAllLettersStrig(_value);
	}


	static short CountSmallLetter(string Text)
	{
		short Count = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (islower(Text[i]))
				Count++;
		}
		return Count;
	}
	short CountSmallLetter()
	{
		return CountSmallLetter(_value);
	}


	static short CountCapitalLetter(string Text)
	{
		short Count = 0;

		for (short i = 0; i < Text.length(); i++)
		{
			if (isupper(Text[i]))
				Count++;
		}
		return Count;
	}
	short CountCapitalLetter()
	{
		return CountCapitalLetter(_value);
	}


	enum enWhatToCount
	{
		SmallLetters = 0,
		CapitalLetters = 1,
		All = 3
	};
	static short CountLetters(string S1, enWhatToCount WhatToCount = enWhatToCount::All)
	{
		if (WhatToCount == enWhatToCount::All)
		{
			return S1.length();
		}

		short Count = 0;
		for (short i = 0; i < S1.length(); i++)
		{
			if (WhatToCount == enWhatToCount::CapitalLetters && isupper(S1[i]))
				Count++;

			if (WhatToCount == enWhatToCount::SmallLetters && islower(S1[i]))
				Count++;
		}

		return Count;
	}
	short CountLetters(enWhatToCount WhatToCount = enWhatToCount::All)
	{
		return CountLetters(_value, WhatToCount);
	}


	static short CountLetter(string S1, char Letter)
	{
		short Count = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (S1[i] == Letter)
				Count++;
		}

		return Count;
	}
	short CountLetter(char Letter)
	{
		return CountLetter(_value, Letter);
	}


private:static bool IsVowel(char Letter)
{
	Letter = tolower(Letter);
	return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
}
public:
	static short CountVowels(string S1)
	{
		short Count = 0;

		for (int i = 0; i < S1.length(); i++)
		{
			if (IsVowel(S1[i]))
				Count++;
		}
		return Count;
	}
	short CountVowels()
	{
		return CountVowels(_value);
	}


	static void PrintEachWordInString(string S1)
	{
		cout << "\nYour string Words are: \n\n";

		string delim = " ";
		string sWord;
		short Pos = 0;

		while ((Pos = S1.find(delim)) != string::npos)
		{
			sWord = S1.substr(0, Pos);

			if (sWord != "")
			{
				cout << sWord << endl;
			}
			S1.erase(0, Pos + delim.length());
		}

		if (S1 != "")
		{
			cout << sWord << endl;
		}
	}
	void PrintEachWordInString()
	{
		PrintEachWordInString(_value);
	}


	static short CountWords(string S1)
	{

		string delim = " ";
		short Count = 0;
		short Pos = 0;
		string sWord;

		while ((Pos = S1.find(delim)) != string::npos)
		{
			sWord = S1.substr(0, Pos);

			if (sWord != "")
			{
				Count++;
			}
			S1.erase(0, Pos + delim.length());
		}

		if (S1 != "")
		{
			Count++;
		}
		return Count;
	}
	short CountWords()
	{
		return CountWords(_value);
	}


	static string RemovePunctuationsFromString(string S1)
	{
		string S2 = "";

		for (int i = 0; i < S1.length(); i++)
		{
			if (!ispunct(S1[i]))
			{
				S2 += S1[i];
			}
		}
		return S2;
	}
	void RemovePunctuationsFromString()
	{
		_value = RemovePunctuationsFromString(_value);
	}


	void printLine()
	{
		cout << _value << endl;
	}
};

