#include<iostream>
#include<iomanip>
using namespace std;

struct Date
{
	int day;
	int month;
	int year;
	Date (int _day, int _month, int _year)
	{
		day = _day;
		month = _month;
		year = _year;
	}
	void print()
	{
		cout << setw(2) << setfill('0') << day << "-" << setw(2) << setfill('0') << month << "-" << year << endl;
	}
};

bool checkdate(Date n)
{
    if (n.month == 1 || n.month == 3 || n.month == 5 || n.month == 7 || n.month == 8 || n.month == 10 || n.month == 12)
    {
        if (n.day < 32 && n.day > 0)
        {
            return true;
        }
        else return false;
    }
    else if (n.month == 4 || n.month == 6 || n.month == 9 || n.month == 11)
    {
        if (n.day < 31 && n.day > 0)
        {
            return true;
        }
        else return false;
    }
    else if (n.month == 2)
    {
        if (n.year % 4 == 0 && (n.year % 100 !=0 || n.year % 400 == 0))
        {
            if (n.day < 30 && n.day > 0)
            {
                return true;
            }
            else return false;
        }
        else
        {
            if (n.day < 29 && n.day > 0)
            {
                return true;
            }
            else return false;
        }
    }
    else return false;
}

bool leapyear(Date);
int Dayinmonth(int);
int Dayinyear(Date);
Date Result(Date, int); // lam not ham nay

int main(int argc, char* argv [])
{
	int day, month, year;
	char c;
	int k;
	cin >> day >> c >> month >> c >> year;
	Date d(day, month, year);
	while(!checkdate(d))
	{
		cout << "Invalid date, please enter the date again.\n";
		cin >> day >> c >> month >> c >> year;
		d.day = day;
		d.month = month;
		d.year = year;
	}
	d.print();
	do
	{
		cin >> k;
		Date d1 = Result(d, k);
		if(k)
		d1.print();
	}
	while(k);		
	return 0;
}

bool leapyear(int y)
{
	if(y % 4 == 0 && (y % 100 != 0 || y % 400 == 0))
	{
		return true;
	}
	else return false;
}

int Dayinmonth(Date d)
{
	switch(d.month)
	{
		case 1:
			return 31;
		case 2:
			if(leapyear(d.year))
			return 29;
			else return 28;
		case 3:
			return 31;
		case 4:
			return 30;
		case 5: 
			return 31;
		case 6:
			return 30;
		case 7:
			return 31;
		case 8:
			return 31;
		case 9:
			return 30;
		case 10:
			return 31;
		case 11:
			return 30;
		case 12:
			return 31;
	}
}

int Dayinyear(Date d)
{
	if(leapyear(d.year)) return 366;
	else return 365;
}

Date Result(Date n, int k)
{
	int kday = n.day + k;
	if(kday <= Dayinmonth(n) && kday > 0)
	{
		n.day = kday;
	}
	else if(kday > 0)
	{
		while(kday >= Dayinmonth(n))
		{
			kday = kday - Dayinmonth(n);
			n.day = kday;
			n.month++;
		}
	}
	else
	{
		do
		{
			n.month--;
			kday = Dayinmonth(n) + kday; 
			n.day = kday;			
		}
		while(-kday >= Dayinmonth(n));
	}
	return n;
}
