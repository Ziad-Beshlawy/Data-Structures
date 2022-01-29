#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include "meeting.h"
#include <cassert>
#include <cstring>
#include <sstream>

using namespace std;
void print(meeting* root);
void clean(meeting* bt);

int main(int argc, char** argv)
{
  if(argc != 2)
    {
		cout << "Invalid arguments."<<endl;
		return 0;
	}
    ifstream Commands ;
    Commands.open (argv[1]);
    if (! Commands )
    {
        cout<<"File not Found"<<endl;
        return 0;
    }

    string commandLine;
	string command;
	char c;
	meeting* root;
	root = new meeting;
	meeting* retrievedMeeting;
	while(getline(Commands, commandLine))
    {
	string arg1;
	string arg2;
	string arg3;
	int int1,int2,int3;
	bool valid_day = true;
	bool valid_hour = true;

		stringstream line;
		line.str(commandLine);
		if(!(line >> command))
        {
			cout << "Invalid arguments."<<endl;//if command line is empty
			continue;
		}
		if(command == "ADD")
        {
        line >> c;
	    arg1 += c;
	    if(c == '\"')
	    {
		while(line.get(c))
		{
			arg1 += c;
			if(c == '\"') break;
		}
	    }
	    else
	    {
		cout << "Invalid title" << endl; //if no quote found
		continue;
	    }
	    if(line >> arg2 >> arg3)
	    {	
			try
			{
				for(char a : arg2)
				{
					if(a == '.') valid_day = false;
				}
				int2 = stoi(arg2);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid day" << endl;
					continue;
			}
			try
			{
				for(char a : arg3)
				{
					if(a == '.') valid_hour = false;
				}
				int3 = stoi(arg3);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid hour" << endl;
					continue;
			}
			if(line >> c)
			{
				cout << "Invalid arguments" << endl;
				continue;
			}
			if(int2 > 365 || int2 < 0 || !valid_day)
			{	
				cout << "Invalid day" << endl;
				continue;
			}
			if(int3 > 23 || int3 < 0 || !valid_hour)
			{
				cout << "Invalid hour"<<endl;
				continue;
			}
	    	if(!(root->insert(arg1, int2, int3)))
			{
				cout << "Conflict " << int2 << " " << int3 << endl;
			}
	    }
	    else
	    {
	    	cout << "Invalid arguments." << endl;
	    }


		}
		else if(command == "Find")
        {
			
	    if(line >> arg1 >> arg2)
	    {	
			try
			{
				for(char a : arg1)
				{
					if(a == '.') valid_day = false;
				}
				int1 = stoi(arg1);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid day" << endl;
					continue;
			}
			try
			{
				for(char a : arg2)
				{
					if(a == '.') valid_hour = false;
				}
				int2 = stoi(arg2);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid hour" << endl;
					continue;
			}

			if(line >> c)
			{
				cout << "Invalid arguments" << endl;
				continue;
			}
			if(int1 > 365 || int1 < 0 || !valid_day)
			{	
				cout << "Invalid day" << endl;
				continue;
			}
			if(int2 > 23 || int2 < 0 || !valid_hour)
			{
				cout << "Invalid hour" <<endl;
				continue;
			}
		retrievedMeeting = root->retrieve(int1, int2);
		if(retrievedMeeting->Empty()) cout << "Empty " << int1 << " " << int2 <<endl;
		else
		{
			cout << retrievedMeeting->gettitle() << endl;;
		}
	    }
	    else
	    {
	    	cout << "Invalid arguments." << endl;
	    }

		}
		else if(command == "MOD")
        {
        line >> c;
	    arg1 += c;
	    if(c == '\"')
	    {
		while(line.get(c))
		{
			arg1 += c;
			if(c == '\"') break;
		}
	    }
	    else
	    {
		cout << "Invalid title" << endl; //if no quote found
		continue;
	    }

	    if(line >> arg2 >> arg3)
	    {
			try
			{
				for(char a : arg2)
				{
					if(a == '.') valid_day = false;
				}
				int2 = stoi(arg2);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid day" << endl;
					continue;
			}
			try
			{
				for(char a : arg3)
				{
					if(a == '.') valid_hour = false;
				}
				int3 = stoi(arg3);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid hour" << endl;
					continue;
			}

			if(line >> c)
			{
				cout << "Invalid arguments" << endl;
				continue;
			}
			if(int2 > 365 || int2 < 0 || !valid_day)
			{	
				cout << "Invalid day" << endl;
				continue;
			}
			if(int3 > 23 || int3 < 0 || !valid_hour)
			{
				cout << "Invalid hour"<<endl;
				continue;
			}
	    	retrievedMeeting = root->retrieve(int2, int3);
		if(retrievedMeeting->Empty()) cout << "Empty " << int2 << " " << int3 << endl;
		else
		{
			retrievedMeeting->changeTitle(arg1);
		}
	    }
	    else
	    {
	    	cout << "Invalid arguments." << endl;
	    }

		}

		else if(command == "DEL")
        {
	    if(line >> arg1 >> arg2)
	    {
			try
			{
				for(char a : arg1)
				{
					if(a == '.') valid_day = false;
				}
				int1 = stoi(arg1);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid day" << endl;
					continue;
			}
			try
			{
				for(char a : arg2)
				{
					if(a == '.') valid_hour = false;
				}
				int2 = stoi(arg2);
			}
			catch(const invalid_argument& ia)
			{
					cout << "Invalid hour" << endl;
					continue;
			}

			if(line >> c)
			{
				cout << "Invalid arguments" << endl;
				continue;
			}
			if(int1 > 365 || int1 < 0 || !valid_day)
			{	
				cout << "Invalid day" << endl;
				continue;
			}
			if(int2 > 23 || int2 < 0 || !valid_hour)
			{
				cout << "Invalid hour"<<endl;
				continue;
			}
	    	retrievedMeeting = root->retrieve(int1, int2);
		if(retrievedMeeting->Empty()) cout << "Empty " << int1 << " " << int2 <<endl;
		else
		{
			retrievedMeeting->Delete();
		}
	    }
	    else
	    {
	    	cout << "Invalid arguments." << endl;
	    }

		}
        else if(command == "Print")
        {
            if(line >> c)
			cout <<"Invalid arguments."<<endl;
			else
			{
				if(root->Empty())
					cout << "Empty Planner" << endl;
				else
				{
					print(root);
				}
			}
        }
		else
		{
			cout << "Invalid command" << endl;
		}
	}
	
	clean(root);

    return 0;
}

void print(meeting* bt)
{
	if(bt->Empty()) return;
	print(bt->left());
	cout<< bt->gettitle()<<" "<< bt->getday() << " " << bt->gethour()<<endl;
	print(bt->right());
	return;
}

void clean(meeting* bt)
{
	if(bt->Empty())
	{
		delete bt;
		return;
	}
	clean(bt->left());
	clean(bt->right());
	delete bt;
	return;
}
