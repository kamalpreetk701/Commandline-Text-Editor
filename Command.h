//provides the declaration of command class
#include<iostream>

using namespace std;
using std::string;
#ifndef COMMAND_H
#define COMMAND_H

class Command
{
		char cmd='\0';			//command name
		int  start=-1;			//startline
		int end=-1;				//end line
public:	char getcmd();			//gets the command name
		int getstart();			//gets the startline
		int getend();			//gets the endline
		
	string removeSpace(string);		//remove all the spaces from command
	string removeTabs(string);		//removes all the tabs from command
	bool is_number(string);			//checks if string is a number or not
	Command parse(string,int,int);	//parses the given command



};

#endif