#include"../header/header.h"

int isLeapYear(int year)
{
	if((year%4==0 && year%100!=0) || year%400==0)
	{
		return 1;
	}
	return 0;
}

int isValidDate(int day,int month,int year)
{
	if(year<1 || month<1 || month>12 || day<1)
	{
		return 0;
	}
	
	int daysInMonth[]={31,28,31,30,31,31,31,31,30,31,30,31};
	if(isLeapYear(year))
	{
		daysInMonth[1]=29;
		
	}
		
	if(day>daysInMonth[month-1])
	{
		return 0;
	}
	return 1;
}
int isValidAge(int birth_day,int birth_month,int birth_year)
{
	time_t t=time(NULL);
	struct tm *current_time=localtime(&t);
	int current_year=current_time->tm_year+1900;
	int current_month=current_time->tm_mon+1;
	int current_day=current_time->tm_mday;

	int age=current_year - birth_year;
	if(current_month < birth_month || (current_month==birth_month && current_day < birth_day))
	{
		age--;
	}
	return age;
}