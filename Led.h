//provides the declaration of led class
#include<iostream>

#include "Command.h"
#include<string>
#include<list>
using std::string;
using namespace std;

#ifndef LED_H
#define LED_H

class Led
{
private:
	int current_line;		
	int last_line;
	int count=0;
	string filename="";			//name of the file
	list<string>buffer;
	list<string>::iterator i_first;		//iterator to begining of buffer
	list<string>::iterator i_last;		//iterator to end of buffer
	list<string>::iterator i_current;	//iterator to current line of buffer
	bool saved = true;

public:	Led();							//default constructor
		
	Led(const string &);				//conversion constructor
	void run();							//run the given command
	void execute(Command c);			//calls the required function to execute the command
	void remove(Command c);				//removes the given lines by user from the buffer
	void insert(Command c);				//insert the given content on the given line in the buffer
	void print(Command c);				//print the given lines
	void append(Command c);				//append the given content after the given line in the buffer
	void change(Command c);				//change the string with the reperesented text in buffer
	void enter(Command c);				//moves the current line down by one
	void write(Command c);				//write the contents of bufferin the file 
	void up(Command c);					//moves the current line up by given lines
	void down(Command c);				//moves the current line down by given lines
	void line_number(Command c);		//prints the content of buffer with line number
	void equal_to(Command c);			//prints the number of current line
	void quit(Command c);				//save the file before quiting

};

#endif