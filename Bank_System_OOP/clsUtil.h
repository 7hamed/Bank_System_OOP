#pragma once

#include <iostream>
#include <vector>
#include <ctime> // to can us " time "
#include <cstdlib> // to can us " srand , rand "
#include "clsDate.h"
using namespace std;


class clsUtil
{

public:
    enum enCharTypes { SmallLetter = 1, CapitalLetter = 2, SpecialLetter = 4, Digit = 3, Mix = 5 };

    static void srand()
    {
        //Seeds the random number generator in C++, called only once
        std::srand((unsigned)time(NULL));
    }

    static int randomNumber(int From, int To)
    {
        return rand() % (To - From + 1) + From;
    }

    static char getRandomCharType(enCharTypes charType)
    {
        if (charType == enCharTypes::Mix)
        {
            charType = enCharTypes(randomNumber(1, 3));
        }
        
        switch (charType)
        {
        case enCharTypes::Digit:
            return char(randomNumber(48, 57));
            break;
        case enCharTypes::SmallLetter:
            return char(randomNumber(97, 122));
            break;
        case enCharTypes::CapitalLetter:
            return char(randomNumber(65, 90));
            break;
        case enCharTypes::SpecialLetter:
            return char(randomNumber(32, 47));
            break;

        default:
            break;
        };
    }

    static string generateWord(enCharTypes charType, short wordLength)
    {
        string theWord = "";

        for (short i = 0; i < wordLength; i++)
        {
            theWord += getRandomCharType(charType);
        }

        return theWord;
    }

    static string generateKey(enCharTypes charType)
    {
        string theKey = "";

        for (short i = 0; i < 4; i++)
        {
            theKey += generateWord(charType, 4);
            
            if (i < 3) theKey += "-";
        }

        return theKey;
    }
    
    static vector<string> generateKeys(enCharTypes charType, short numberOfKeys)
    {
        vector<string> theKeys;

        for (short i = 0; i < numberOfKeys; i++)
        {
            theKeys.push_back(generateKey(charType));
        }

        return theKeys;
    }


    static void fillArrayWithRandomNumbers(int* arr, int length, int from, int to)
    {
        for (int i = 0; i < length; i++)
        {
            arr[i] = randomNumber(from, to);
        }
    }

    static void fillArrayRandomWords(string* arr, int length, enCharTypes charType, short wordLength)
    {
        for (int i = 0; i < length; i++)
        {
            arr[i] = generateWord(charType, wordLength);
        }
    }

    static void fillArrayWithRandomKeys(string* arr, int length, enCharTypes charType)
    {
        for (int i = 0; i < length; i++)
        {
            arr[i] = generateKey(charType);
        }
    }


    static void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }

    static void swap(double& a, double& b)
    {
        double temp = a;
        a = b;
        b = temp;
    }

    static void swap(short& a, short& b)
    {
        short temp = a;
        a = b;
        b = temp;
    }

    static void swap(float& a, float& b)
    {
        float temp = a;
        a = b;
        b = temp;
    }

    static void swap(string& a, string& b)
    {
        string temp = a;
        a = b;
        b = temp;
    }

    static void swap(clsDate& a, clsDate& b)
    {
        clsDate::swapDates(a, b);
    }


    static void shuffleArray(int* arr, int length)
    {
        int randomNum;
        
        for (int i = 0; i < length; i++)
        {
            randomNum = randomNumber(0, length - 1);

            swap(arr[i], arr[randomNum]);
        }
    }

    static void shuffleArray(string* arr, int length)
    {
        int randomNum;
        for (int i = 0; i < length; i++)
        {
            randomNum = randomNumber(0, length - 1);

            swap(arr[i], arr[randomNum]);
        }
    }

    static string tabs(short numberOfTabs)
    {
        string t = "";
        for (short i = 0; i < numberOfTabs; i++)
        {
            t += "\t";
        }
        return t;
    }

    static string encryptionText(string OriginalText)
    {
        int textLength = OriginalText.length();
        string newText = "";

        for (int i = 0; i < textLength; i++)
        {
            if (i % 2 == 0)
            {
                OriginalText[i] = OriginalText[i] + 2;
            }
            else
            {
                OriginalText[i] = OriginalText[i] + 1;
            }
        }

        newText = OriginalText;
        return newText;
    }

    static string decryptionText(string OriginalText)
    {
        int textLength = OriginalText.length();
        string newText = "";

        for (int i = 0; i < textLength; i++)
        {
            if (i % 2 == 0)
            {
                OriginalText[i] = OriginalText[i] - 2;
            }
            else
            {
                OriginalText[i] = OriginalText[i] - 1;
            }
        }

        newText = OriginalText;
        return newText;
    }

    static string numberToText(int number)
    {
        
        if (number == 0)
            return "";

        if (number >= 1 && number <= 19)
        {
            string arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
            "Sixteen", "Seventeen", "Eighteen", "Nineteen" };

            return arr[number];
        }

        if (number >= 20 && number <= 99)
        {
            string arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Six",
            "Seventy", "Eighty", "Ninty" };

            return arr[number / 10] + " " + numberToText(number % 10);
        }

        if (number >= 100 && number <= 199)
        {
            return "One Hundred " + numberToText(number % 100);
        }

        if (number >= 200 && number <= 999)
        {
            return numberToText(number / 100) + " Hundreds " + numberToText(number % 100);
        }

        if (number >= 1000 && number <= 1999)
        {
            return "One Thousands " + numberToText(number % 1000);
        }

        if (number >= 2000 && number <= 999999)
        {
            return numberToText(number / 1000) + " Thousands " + numberToText(number % 1000);
        }

        if (number >= 1000000 && number <= 1999999)
        {
            return "One Million " + numberToText(number % 1000000);
        }

        if (number >= 2000000 && number <= 999999999)
        {
            return numberToText(number / 1000000) + " Millions " + numberToText(number % 1000000);
        }

        if (number >= 1000000000 && number <= 1999999999)
        {
            return "One Billion " + numberToText(number % 1000000000);
        }
        else
        {
            return numberToText(number / 1000000000) + " Billions " + numberToText(number % 1000000000);
        }


    }

};