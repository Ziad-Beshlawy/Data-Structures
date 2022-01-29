#include <iostream>
#include <string>
#include "meeting.h"
#include <cassert>
#include <cstring>

using namespace std;
meeting::meeting()
{
    nullTree = true;
    leftTree = NULL;
    rightTree = NULL; 
}


bool meeting::Empty()const
{
    return nullTree;
}
string meeting::gettitle()const
{
    assert(!nullTree);
    return title;
}
int meeting::getday()const
{
    assert(!nullTree);
    return day;
}
int meeting::gethour()const
{
    assert(!nullTree);
    return hour;
}
meeting* meeting::left()
{
     assert(!nullTree);
     return leftTree;

}
meeting* meeting:: right()
{
     assert(!nullTree);
     return rightTree;

}


bool meeting::insert(const string &addedTitle, const int &addedDay, const int &addedHour)
//returns true when item is added successfully, false when item already exists.
{
	if(nullTree)
	{
		nullTree =false;
		title = addedTitle;
		day = addedDay;
		hour = addedHour;
		leftTree = new meeting;
		rightTree = new meeting;
		return true;
	}
	else if(addedDay < day)
	{		
		return leftTree->insert(addedTitle, addedDay, addedHour);
	}
	else if(addedDay > day)
	{
		return rightTree->insert(addedTitle, addedDay, addedHour);
	}
	else//found the same day
	{
		if(addedHour < hour)
		{
			return leftTree->insert(addedTitle, addedDay, addedHour);
		}
		else if(addedHour > hour)
		{
			return rightTree->insert(addedTitle, addedDay, addedHour);
		}
		else//found same day and hour
		{
			return false;
		}
	}
}

meeting* meeting::retrieve(const int &addedDay, const int &addedHour)
{
	if(nullTree || ((day == addedDay) && (hour == addedHour)))
	{
		return this;
	}
	else if(addedDay < day)
	{
		return leftTree->retrieve(addedDay, addedHour);
	}
	else if(addedDay > day)
	{
		return rightTree->retrieve(addedDay, addedHour);
	}
	else
	{
		if(addedHour < hour)
		{
			return leftTree->retrieve(addedDay, addedHour);
		}
		else if(addedHour > hour)
		{
			return rightTree->retrieve(addedDay, addedHour);
		}
	}
}

void meeting::changeTitle(const string &addedTitle)
{
	title = addedTitle;
	return;
}

void meeting::Delete()
 {
 	if(!rightTree->Empty())
 	{
		title = rightTree->title;
		day = rightTree->day;
		hour = rightTree->hour;
		rightTree->Delete();
 	}
	else if(!leftTree->Empty())
	{
		title = leftTree->title;
		day = leftTree->day;
		hour = leftTree->hour;
		leftTree->Delete();
	}
	else
	{
		nullTree = true;
		delete leftTree;
		delete rightTree;
	}
 }

