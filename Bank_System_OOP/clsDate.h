#pragma warning(disable : 4996)
#pragma once // change private to _day, ... and make property with Day Camel style

#include <iostream>
#include <vector>
#include <string>
#include "clsString.h"


using namespace std;


class clsDate
{

private:
    short day;
    short month;
    short year;

public: // property [get; set;]
    short getDay() { return this->day; }
    void setDay(short value) { this->day = value; }

    short getMonth() { return this->month; }
    void setMonth(short value) { this->month = value; }

    short getYear() { return this->year; }
    void setYear(short value) { this->year = value; }


public: // constructors

    clsDate() // no parameters = default constructor
    {
        //*this = getDateSystem(); // this get error : this inside the default constructor, The object is still being constructed, and you’re trying to assign to it.

        time_t nowSeconds = time(0); // t = million of seconds
        tm nowTimeStruct;
        localtime_s(&nowTimeStruct, &nowSeconds);

        this->day = nowTimeStruct.tm_mday;
        this->month = nowTimeStruct.tm_mon + 1;
        this->year = nowTimeStruct.tm_year + 1900;

    }

    clsDate(string dateString)
    {
        *this = clsDate::stringToDate(dateString); // this work fine 
    }

    clsDate(short day, short month, short year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    clsDate(short daysNumber, short year)
    {
        this->day = 1;
        this->month = 1;
        this->year = year;

        *this = increaseDateByXDays(*this, daysNumber);
    }


private:
    static int readNumber(string Message) // why static : not depend to any object data
    {
        int num;

        cout << Message;
        cin >> num;

        while (cin.fail()) // validation number
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << "EROR, " + Message;
            cin >> num;
        }

        return num;
    }

    static short readYear()
    {
        short y = -1;

        while (y < 0)
        {
            y = readNumber("plese enter a year : ");
        }

        return y;
    }

    static short readMonth()
    {
        short m = -1;

        while (m < 1 || m > 12)
        {
            m = readNumber("please enter a month : ");
        }

        return m;
    }

    static short readDay()
    {
        short d = -1;

        while (d < 1 || d > 31)
        {
            d = readNumber("please enter a day : ");
        }

        return d;
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


public: // date methods

    static string toString(clsDate d)
    {
        return to_string(d.day) + "/" + to_string(d.month) + "/" + to_string(d.year);
    }
    string toString()
    {
        return toString(*this);
    }


    static clsDate stringToDate(string dateString)
    {
        vector<string> dateElement = clsString::split(dateString, "/");

        short d, m, y;
        d = stoi(dateElement[0]);
        m = stoi(dateElement[1]);
        y = stoi(dateElement[2]);

        return clsDate(d, m, y);
    }


    static bool isLastDayInMonth(clsDate d)
    {
        return d.day == numberOfDaysInMonth(d.month, d.year);
    }
    bool isLastDayInMonth()
    {
        return isLastDayInMonth(*this);
    }


    static bool isLastMonthInYear(clsDate d)
    {
        return d.month == 12;
    }
    bool isLastMonthInYear()
    {
        return isLastMonthInYear(*this);
    }


    static clsDate readDateFromConsole()
    {
        short d, m, y;

        d = readDay();
        m = readMonth();
        y = readYear();

        return clsDate(d, m, y);
    }


    static string monthsShortName(short monthNumber)
    {
        if (monthNumber < 1 || monthNumber > 12) return "Error";

        string arr[] = { "", "Jan", "Feb", "Mar", "Apr", "May", "Jun",
        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

        return arr[monthNumber];
    }


    static string daysShortName(short dayOrderNumber)
    {
        if (dayOrderNumber < 0 || dayOrderNumber > 7) return "Error";

        string arr[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

        return arr[dayOrderNumber];
    }


    static bool isLeapYear(short year)
    {
        return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
    }
    static bool isLeapYear(const clsDate& d)
    {
        return isLeapYear(d.year);
    }
    bool isLeapYear()
    {
        return isLeapYear(*this);
    }


    static short numberOfDaysInYear(short year)
    {
        return isLeapYear(year) ? 366 : 365;
    }
    static short numberOfDaysInYear(const clsDate& d)
    {
        return numberOfDaysInYear(d.year);
    }
    short numberOfDaysInYear()
    {
        return numberOfDaysInYear(*this);
    }


    static short numberOfDaysInMonth(short month, short year)
    {
        if (month < 1 && month > 12) return 0;

        int arr[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return (month == 2 ? (isLeapYear(year) ? 29 : 28) : (arr[month]));
    }
    static short numberOfDaysInMonth(const clsDate& d)
    {
        return numberOfDaysInMonth(d.month, d.year);
    }
    short numberOfDaysInMonth()
    {
        return numberOfDaysInMonth(*this);
    }


    static short dayOfWeekOrderNumber(short day, short month, short year)
    {
        short a = floor((14 - month) / 12);
        short y = year - a;
        short m = month + 12 * a - 2;

        return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    static short dayOfWeekOrderNumber(const clsDate& date)
    {
        return dayOfWeekOrderNumber(date.day, date.month, date.year);
    }
    short dayOfWeekOrderNumber()
    {
        return dayOfWeekOrderNumber(*this);
    }


    static short numberOfDaysFromTheBeginingOfTheYear(short day, short month, short year)
    {
        short totalDays = 0;

        for (int i = 1; i < month; i++)
        {
            totalDays += numberOfDaysInMonth(i, year);
        }

        return totalDays + day;
    }
    static short numberOfDaysFromTheBeginingOfTheYear(const clsDate& d)
    {
        return numberOfDaysFromTheBeginingOfTheYear(d.day, d.month, d.year);
    }
    short numberOfDaysFromTheBeginingOfTheYear()
    {
        return numberOfDaysFromTheBeginingOfTheYear(*this);
    }


    static bool isDate1BeforeDate2(clsDate d1, clsDate d2)
    {
        return d1.year < d2.year ? true : (d1.year == d2.year ? (d1.month < d2.month ? true : (d1.month == d2.month ? d1.day < d2.day : false)) : false);
    }
    bool isDateBeforeDate2(const clsDate& date2)
    {
        return isDate1BeforeDate2(*this, date2);
    }


    static bool isDate1EqualDate2(clsDate d1, clsDate d2)
    {
        return d1.day != d2.day ? false : (d1.month != d2.month ? false : (d1.year != d2.year ? false : true));
    }
    bool isDateEqualDate2(const clsDate& date2)
    {
        return isDate1EqualDate2(*this, date2);
    }


    static bool isDate1AfterDate2(clsDate date1, clsDate date2)
    {
        return !isDate1BeforeDate2(date1, date2) && !isDate1EqualDate2(date1, date2);
    }
    bool isDateAfterDate2(const clsDate& date2)
    {
        return isDate1AfterDate2(*this, date2);
    }

    enum enDateCompare { Before = -1, Equal = 0, After = 1 };
    static enDateCompare compareDate(clsDate date1, clsDate date2)
    {
        if (isDate1BeforeDate2(date1, date2))
            return enDateCompare::Before;

        else if (isDate1EqualDate2(date1, date2))
            return enDateCompare::Equal;
        else
            return enDateCompare::After;
    }
    enDateCompare compareToDate2(const clsDate& date2)
    {
        return compareDate(*this, date2);
    }


    static void printMonthCalendar(short month, short year)
    {
        short cur = dayOfWeekOrderNumber(1, month, year); // start Calendar from this day
        short monthDaysNumber = numberOfDaysInMonth(month, year); // how many day in month

        printf("\n  _______________%s_______________\n", monthsShortName(month).c_str()); // print title
        printf("\n  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");


        for (int i = 0; i < cur; i++) // print the empty days
            printf("     ");

        int endline = cur;
        for (int i = 1; i <= monthDaysNumber; i++) // print days continusly
        {
            printf("%5d", i);

            if (++endline == 7) // next line
            {
                printf("\n");
                endline = 0;
            }
        }

        printf("\n  _________________________________\n");
    }
    static void printMonthCalendar(const clsDate& d)
    {
        printMonthCalendar(d);
    }
    void printMonthCalendar()
    {
        printMonthCalendar(*this);
    }


    static void printYearCalendar(short year)
    {
        cout << "\n  _________________________________\n\n";
        cout << "          Calendar - " << year;
        cout << "\n  _________________________________\n";


        for (int i = 1; i <= 12; i++)
        {
            printMonthCalendar(i, year);
            cout << endl;
        }
    }
    static void printYearCalendar(const clsDate& d)
    {
        printYearCalendar(d.year);
    }
    void printYearCalendar()
    {
        printYearCalendar(*this);
    }


    static void swapDates(clsDate& date1, clsDate& date2)
    {
        clsDate temp = date1;
        date1 = date2;
        date2 = temp;
    }


    static int getDiffDates(clsDate date1, clsDate date2, bool includeEndDay = false)
    {
        short swapFlagValue = 1;
        if (!isDate1BeforeDate2(date1, date2))
        {
            swapDates(date1, date2);

            swapFlagValue = -1;
        }

        int days = 0;
        while (isDate1BeforeDate2(date1, date2))
        {
            days++;
            date1 = increaseDateByOneDay(date1);
        }

        return (includeEndDay ? (days + 1) * swapFlagValue : days * swapFlagValue);
    }
    int getDiffToDate2(const clsDate& date2, bool includeEndDay = false)
    {
        return getDiffDates(*this, date2, includeEndDay);
    }


    static clsDate getDateSystem()
    {
        short d, m, y;

        time_t nowSeconds = time(0); // t = million of seconds
        tm nowTimeStruct;
        localtime_s(&nowTimeStruct, &nowSeconds);

        d = nowTimeStruct.tm_mday;
        m = nowTimeStruct.tm_mon + 1;
        y = nowTimeStruct.tm_year + 1900;

        return clsDate(d, m, y);
    }


    /*  INCREASE DATE  */

    static clsDate increaseDateByOneDay(clsDate date)
    {
        if (isLastDayInMonth(date))
        {
            if (isLastMonthInYear(date))
            {
                date.day = 1;
                date.month = 1;
                date.year++;
            }
            else
            {
                date.day = 1;
                date.month++;
            }
        }
        else
        {
            date.day++;
        }

        return date;
    }
    void increaseDateByOneDay()
    {
        *this = increaseDateByOneDay(*this);
    }


    // 1.
    static clsDate increaseDateByXDays(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = increaseDateByOneDay(date);

        return date;
    }
    void increaseDateByXDays(int x)
    {
        *this = increaseDateByXDays(*this, x);
    }


    // 2.
    static clsDate increaseDateByOneWeek(clsDate date)
    {
        return increaseDateByXDays(date, 7);
    }
    void increaseDateByOneWeek()
    {
        *this = increaseDateByOneWeek(*this);
    }


    // 3.
    static clsDate increaseDateByXWeeks(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = increaseDateByOneWeek(date);

        return date;
    }
    void increaseDateByXWeeks(int x)
    {
        *this = increaseDateByXWeeks(*this, x);
    }


    // 4.
    static clsDate increaseDateByOneMonth(clsDate date)
    {
        //return increaseDateByXDays(date, numberOfDaysInMonth(date.month, date.year));

        if (date.month >= 12)
        {
            date.month = 1;
            date.year++;
        }
        else
        {
            date.month++;
        }

        // maybe the date is 29.1.2001 and the result is 29.2.2001, and this wrong
        short daysNumberInMonth = numberOfDaysInMonth(date.month, date.year);
        if (date.day > daysNumberInMonth)
        {
            date.day = daysNumberInMonth;
        }

        return date;
    }
    void increaseDateByOneMonth()
    {
        *this = increaseDateByOneMonth(*this);
    }


    // 5.
    static clsDate increaseDateByXMonths(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = increaseDateByOneMonth(date);

        return date;
    }
    void increaseDateByXMonths(int x)
    {
        *this = increaseDateByXMonths(*this, x);
    }


    // 6.
    static clsDate increaseDateByOneYear(clsDate date)
    {
        //return increaseDateByXDays(date, numberOfDaysInYear(date.year));
        date.year++;
        if (!isLeapYear(date.year))
        {
            if (date.day == 29 && date.month == 2)
            {
                date.day = 28;
            }
        }
        return date;
    }
    void increaseDateByOneYear()
    {
        *this = increaseDateByOneYear(*this);
    }


    // 7.
    static clsDate increaseDateByXYears(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = increaseDateByOneYear(date);

        return date;
    }
    void increaseDateByXYears(int x)
    {
        *this = increaseDateByXYears(*this, x);
    }


    // 8.
    static clsDate increaseDateByXYearsFast(clsDate date, int x)
    {

        date.year += x;
        if (!isLeapYear(date.year))
        {
            if (date.day == 29 && date.month == 2)
            {
                date.day = 28;
            }
        }
        return date;
    }
    void increaseDateByXYearsFast(int x)
    {
        *this = increaseDateByXYearsFast(*this, x);
    }


    // 9.
    static clsDate increaseDateByOneDecade(clsDate date)
    {
        return increaseDateByXYearsFast(date, 10);
    }
    void increaseDateByOneDecade()
    {
        *this = increaseDateByOneDecade(*this);
    }


    // 10.
    static clsDate increaseDateByXDecades(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = increaseDateByOneDecade(date);

        return date;
    }
    void increaseDateByXDecades(int x)
    {
        *this = increaseDateByXDecades(*this, x);
    }


    // 11.
    static clsDate increaseDateByXDecadesFaster(clsDate date, int x)
    {
        date.year += x * 10;

        if (!isLeapYear(date.year))
        {
            if (date.day == 29 && date.month == 2)
            {
                date.day = 28;
            }
        }
        return date;
    }
    void increaseDateByXDecadesFaster(int x)
    {
        *this = increaseDateByXDecadesFaster(*this, x);
    }


    // 12.
    static clsDate increaseDateByOneCentury(clsDate date)
    {
        return increaseDateByXDecadesFaster(date, 10);
    }
    void increaseDateByOneCentury()
    {
        *this = increaseDateByOneCentury(*this);
    }


    // 13.
    static clsDate increaseDateByOneMillennum(clsDate date)
    {
        return increaseDateByXDecadesFaster(date, 100);
    }
    void increaseDateByOneMillennum()
    {
        *this = increaseDateByOneMillennum(*this);
    }



    /*  DECREASE DATE  */

    // 0.
    static clsDate decreaseDateByOneDay(clsDate date)
    {
        if (date.day == 1) // first day of year
        {
            if (date.month == 1) // first month of month
            {
                date.day = 31;
                date.month = 12;
                date.year--;
            }
            else
            {
                date.month--;
                date.day = numberOfDaysInMonth(date.month, date.year);
            }
        }
        else
        {
            date.day--;
        }

        return date;
    }
    void decreaseDateByOneDay()
    {
        *this = decreaseDateByOneDay(*this);
    }


    // 1.
    static clsDate decreaseDateByXDays(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = decreaseDateByOneDay(date);

        return date;
    }
    void decreaseDateByXDays(int x)
    {
        *this = decreaseDateByXDays(*this, x);
    }


    // 2.
    static clsDate decreaseDateByOneWeek(clsDate date)
    {
        return decreaseDateByXDays(date, 7);
    }
    void decreaseDateByOneWeek()
    {
        *this = decreaseDateByOneWeek(*this);
    }


    // 3.
    static clsDate decreaseDateByXWeeks(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = decreaseDateByOneWeek(date);

        return date;
    }
    void decreaseDateByXWeeks(int x)
    {
        *this = decreaseDateByXWeeks(*this, x);
    }


    // 4.
    static clsDate decreaseDateByOneMonth(clsDate date)
    {
        //return decreaseDateByXDays(date, numberOfDaysInMonth(date.month, date.year));

        if (date.month == 1)
        {
            date.month = 12;
            date.year--;
        }
        else
        {
            date.month--;
        }

        // maybe the date is 29.3.2001 and the result is 29.2.2001, and this wrong
        short daysNumberInMonth = numberOfDaysInMonth(date.month, date.year);
        if (date.day > daysNumberInMonth)
        {
            date.day = daysNumberInMonth;
        }

        return date;
    }
    void decreaseDateByOneMonth()
    {
        *this = decreaseDateByOneMonth(*this);
    }


    // 5.
    static clsDate decreaseDateByXMonths(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = decreaseDateByOneMonth(date);

        return date;
    }
    void decreaseDateByXMonths(int x)
    {
        *this = decreaseDateByXMonths(*this, x);
    }


    // 6.
    static clsDate decreaseDateByOneYear(clsDate date)
    {
        //return decreaseDateByXDays(date, numberOfDaysInYear(date.year));
        date.year--;
        if (!isLeapYear(date.year))
        {
            if (date.day == 29 && date.month == 2)
            {
                date.day = 28;
            }
        }
        return date;
    }
    void decreaseDateByOneYear()
    {
        *this = decreaseDateByOneYear(*this);
    }


    // 7.
    static clsDate decreaseDateByXYears(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = decreaseDateByOneYear(date);

        return date;
    }
    void decreaseDateByXYears(int x)
    {
        *this = decreaseDateByXYears(*this, x);
    }


    // 8.
    static clsDate decreaseDateByXYearsFast(clsDate date, int x)
    {

        date.year -= x;
        if (!isLeapYear(date.year))
        {
            if (date.day == 29 && date.month == 2)
            {
                date.day = 28;
            }
        }
        return date;
    }
    void decreaseDateByXYearsFast(int x)
    {
        *this = decreaseDateByXYearsFast(*this, x);
    }


    // 9.
    static clsDate decreaseDateByOneDecade(clsDate date)
    {
        return decreaseDateByXYearsFast(date, 10);
    }
    void decreaseDateByOneDecade()
    {
        *this = decreaseDateByOneDecade(*this);
    }


    // 10.
    static clsDate decreaseDateByXDecades(clsDate date, int x)
    {
        for (int i = 0; i < x; i++)
            date = decreaseDateByOneDecade(date);

        return date;
    }
    void decreaseDateByXDecades(int x)
    {
        *this = decreaseDateByXDecades(*this, x);
    }

    // 11.
    static clsDate decreaseDateByXDecadesFaster(clsDate date, int x)
    {
        date.year -= x * 10;

        if (!isLeapYear(date.year))
        {
            if (date.day == 29 && date.month == 2)
            {
                date.day = 28;
            }
        }
        return date;
    }
    void decreaseDateByXDecadesFaster(int x)
    {
        *this = decreaseDateByXDecadesFaster(*this, x);
    }

    // 12.
    static clsDate decreaseDateByOneCentury(clsDate date)
    {
        return decreaseDateByXDecadesFaster(date, 10);
    }
    void decreaseDateByOneCentury()
    {
        *this = decreaseDateByOneCentury(*this);
    }


    // 13.
    static clsDate decreaseDateByOneMillennum(clsDate date)
    {
        return decreaseDateByXDecadesFaster(date, 100);
    }
    void decreaseDateByOneMillennum()
    {
        *this = decreaseDateByOneMillennum(*this);
    }



    static bool isEndOfWeek(clsDate date) // saturday is end of week
    {
        return dayOfWeekOrderNumber(date) == 6;
    }
    bool isEndOfWeek()
    {
        return isEndOfWeek(*this);
    }


    // 0-sun  1-mon  2-tue  3-wen  4-thu  5-fri  6-sat
    static bool isWeekEnd(clsDate date) // sunday & saturday are weekend
    {
        return (dayOfWeekOrderNumber(date) == 5 || dayOfWeekOrderNumber(date) == 6);
    }
    bool isWeekEnd()
    {
        return isWeekEnd(*this);
    }


    static bool isBusinessDay(clsDate date)
    {
        return !isWeekEnd(date);
    }
    bool isBusinessDay()
    {
        return isBusinessDay(*this);
    }


    static short daysUntilTheEndOfWeek(clsDate date)
    {
        /*while (!isEndOfWeek(date))
            date = increaseDateByOneDay(date);

        return date.day; */

        return 6 - dayOfWeekOrderNumber(date);
    }
    short daysUntilTheEndOfWeek()
    {
        return daysUntilTheEndOfWeek(*this);
    }

    static short daysUntilTheEndOfMonth(clsDate date)
    {
        //return numberOfDaysInMonth(date.month, date.year) - date.day;

        short d, m, y; // endMonthDate
        d = numberOfDaysInMonth(date.month, date.year);
        m = date.month;
        y = date.year;

        return getDiffDates(date, clsDate(d, m, y), true);
    }
    short daysUntilTheEndOfMonth()
    {
        return daysUntilTheEndOfMonth(*this);
    }


    static short daysUntilTHeEndOfYear(clsDate date)
    {
        //return numberOfDaysInYear(date.year) - numberOfDaysFromTheBeginingOfTheYear(date.day, date.month, date.year);

        short d, m, y; // endYearDate
        d = 31;
        m = 12;
        y = date.year;

        return getDiffDates(date, clsDate(d, m, y), true);
    }
    short daysUntilTHeEndOfYear()
    {
        return daysUntilTHeEndOfYear(*this);
    }


    static short vacationCalculator(clsDate dateFrom, clsDate dateTo)
    {
        short count = 0;

        while (isDate1BeforeDate2(dateFrom, dateTo))
        {
            if (isBusinessDay(dateFrom))
                count++;
            dateFrom = increaseDateByOneDay(dateFrom);
        }

        return count;
    }
    short vacationCalculatorToDate2(const clsDate& date2)
    {
        return vacationCalculator(*this, date2);
    }


    static clsDate vacationReturnDateCalculator(clsDate dateFrom, short vacationDays)
    {
        while (vacationDays > 0)
        {
            if (isBusinessDay(dateFrom))
            {
                vacationDays--;
            }

            dateFrom = increaseDateByOneDay(dateFrom);
        }

        return dateFrom;
    }
    clsDate vacationReturnDateCalculator(short vacationDays)
    {
        return vacationReturnDateCalculator(*this, vacationDays);
    }


    static bool isValidDate(clsDate date)
    {
        if (date.year < 0)
            return false;

        if (date.month < 1 || date.month > 12)
            return false;

        if (date.day < 1 || date.day > numberOfDaysInMonth(date.month, date.year))
            return false;

        return true;
    }
    bool isValidDate()
    {
        return isValidDate(*this);
    }


    static string formatDate(clsDate date, string formatDateString = "dd/mm/yyyy")
    {
        string newFormat = "";

        newFormat = replaceWordInString(formatDateString, "dd", to_string(date.day));
        newFormat = replaceWordInString(newFormat, "mm", to_string(date.month));
        newFormat = replaceWordInString(newFormat, "yyyy", to_string(date.year));

        return newFormat;
    }

    static string getSystemDateTimeString()
    {
        time_t t = time(0);
        tm* now = localtime(&t);

        short Day, Month, Year, Hour, Minute, Second;

        Year = now->tm_year + 1900;
        Month = now->tm_mon + 1;
        Day = now->tm_mday;
        Hour = now->tm_hour;
        Minute = now->tm_min;
        Second = now->tm_sec;

        return (to_string(Day) + "/" + to_string(Month) + "/"
            + to_string(Year) + " - "
            + to_string(Hour) + ":" + to_string(Minute)
            + ":" + to_string(Second));
    }

};



