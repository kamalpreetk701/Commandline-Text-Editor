//provides the implementation of command class
#include"Command.h"
#include<iostream>
#include <string>
using namespace std;

char Command::getcmd()			//to get the command name
{
		return cmd;
}

int Command::getstart()			//to get start line
{
	return start;
}

int Command::getend()			//to get end line
{
	return end;
}

string Command::removeSpace(string input)		//remove all the spaces from command
{
	int length = input.length();
	for (int i = length-1; i >=0; i--)
	{
		if (input[i] == ' ')
		{
			input.erase(i,1);
		}
	}
		return input;
}

string Command::removeTabs(string input)			//remove all the tabs from the command
{
	int length = input.length();
	for (int i = length - 1; i >= 0; i--)
	{
		if (input[i] == '\t')
		{
			input.erase(i, 1);
		}
	}
	return input;
}

bool Command::is_number(string str)
{
	bool has_only_digits = true;
	for (size_t n = 0; n < str.length(); n++)
	{
		if (!isdigit(str[n]))
		{
			has_only_digits = false;
			break;
		}
	}
		return has_only_digits;
}


Command Command::parse(string input,int current,int last)		//parse the entered command
{
	removeSpace(input);
	removeTabs(input);
	int loc = input.find(',');
	string before_comma = input.substr(0, loc);
	string after_comma = input.substr(loc + 1, input.length());
	int command1 = input.find('u');
	int command2 = input.find('d');
	
	if (command1 >= 0 || command2 >=0|| input=="")		//checks if command is u or d or enter
	{
		if(input=="")
		{
			cmd = 'e';
		}
		else
		{
			cmd = input.back();
			int loc = input.find(',');
			if (loc < 0 && input.length() == 1)
			{
				end = 1; start = 1;
			}
			else if (loc < 0 && input.length() > 1)
			{
				input.pop_back();
				start = atoi(after_comma.c_str());
				end = atoi(after_comma.c_str());
			}
			else
			{
				if (input.length() > 1)
				{

					if ((input.back() == '.' || input.back() == ',') && input.length() == 1)
					{
						start = 1; end = 1;
					}
					else if (loc > 0 && (after_comma.length() == 1))
					{
						start = atoi(before_comma.c_str());
						end = atoi(before_comma.c_str());
					}
					else if (after_comma.length() != 0)
					{
						start = atoi(after_comma.c_str());
						end = atoi(after_comma.c_str());
					}
					else
					{
						start = atoi(input.c_str());
						end = atoi(input.c_str());
					}
				}
			}
		}
		
	}
	else
	{
												// for all commands other than u and d
	if (loc>=0)											//if comma exits
	{
		
		if (loc == 0 && input.length() == 1)				//only comma
		{
		start = current; end = current; cmd = 'p';
		return *this;
		}

		
		if (before_comma == "." || before_comma == "")		//before comma, start is set
			start = current;
		else if (before_comma == "$")
			start = last;
		else if (is_number(before_comma))
		{
			if(atoi(before_comma.c_str())>last)
			start = last;
				else
				start = atoi(before_comma.c_str());
		}
		else
		{
			start = -1;
			return *this;
		}
		

		int len = after_comma.length();

			if (len == 0)											//no character after comma 
			{
				end = current;	cmd = 'p';
			}
			else if (len == 1)								//one character after comma
			{
				char last_char = after_comma.back();
				if (last_char == '.')
				{
					end = current;
					cmd = 'p';
				}
				else if (isalpha(last_char))
				{
						end = current;
						cmd = last_char;
				}
				else if (last_char=='$')
				{
					end = last;
					cmd = 'p';
				}
				else
				{					
					end = last_char-'0';
					cmd = 'p';
				}
			}
			else if (len > 1)					//more than one character after comma
			{
				char last_char = after_comma.back();
				if (isalpha(last_char))				//if last character is alpha
				{
					cmd = last_char;
					after_comma.pop_back();
					if (after_comma == "$")
						end = last;
					else if (after_comma == ".")
						end = current;
					else
						end = atoi(after_comma.c_str());
				}
				else
				{													//if last character is not alpha
					end = atoi(after_comma.c_str());
					cmd = 'p';
				}
			}
		}
	else													 //no comma in the command
	{
		if (input == "=")
		{
			start = current; end = current; cmd = '=';
		}
		else if(input=="$")
		{
			start = last; end = last; cmd = 'p';
		}
		else if (isalpha(input.back()) && input.length() == 1)
		{
			start = current; end = current; cmd = input[0];
		}
		else
		{
			if (isalpha(input.back()))
			{
				cmd = input.back();
				input.pop_back();
				if (input == "$")
				{
					start = input[0]; end = last;
				}
				else if (input == ".")
				{
					start = current; end = current;
				}
				else
				{	if (is_number(input)&&atoi(input.c_str()) < last)
					{
							if(atoi(input.c_str())>last)
							{
								start = last; end = last;
							}
							else
							{
							start = atoi(input.c_str());
							end = atoi(input.c_str());
						}
					}
					else if(is_number(input))
					{
						start = current;
						end = last;
					}
					else
					{
						start = -1;
						end = -1;
					}
				}
			}
			else if (is_number(input))
				{
					start = atoi(input.c_str());
					end = atoi(input.c_str());
					cmd = 'p';
				}
			else                                        //if command not found
			{
				start = -1; end = -1; cmd = '\0';
			}
			}
	}
	}
	return *this;

	}

	
	

